#include "Renderer.h"
#include "Board.h"
#include <iostream>
#include <algorithm>

Renderer::Renderer() : window(nullptr), renderer(nullptr),
                       screenWidth(1280), screenHeight(720),
                       tileSize(24), viewSizeX(12), viewSizeY(20) {
}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::init(const char* title, int width, int height) {
    screenWidth = width;
    screenHeight = height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow(title,
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             screenWidth, screenHeight,
                             SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Renderer::setDrawColor(Color color) {
    switch(color) {
        case Color::RED:
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
            break;
        case Color::BLUE:
            SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
            break;
        case Color::YELLOW:
            SDL_SetRenderDrawColor(renderer, 255, 220, 50, 255);
            break;
        case Color::MAGNENTA:
            SDL_SetRenderDrawColor(renderer, 255, 50, 255, 255);
            break;
        default:
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            break;
    }
}

void Renderer::drawRect(int x, int y, int w, int h, bool filled) {
    SDL_Rect rect = {x, y, w, h};
    if (filled) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void Renderer::drawTile(std::pair<int,int> pos, char tile, Color tileColor, int screenX, int screenY) {
    int x = screenX * tileSize;
    int y = screenY * tileSize;

    // Draw background
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    drawRect(x, y, tileSize, tileSize, true);

    // Draw tile based on type
    if (tile == '#') {
        // Wall - gray
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        drawRect(x + 1, y + 1, tileSize - 2, tileSize - 2, true);
    }
    else if (tile == '@') {
        // Player - colored circle
        setDrawColor(tileColor);
        // Draw as a circle approximation using filled rect
        int centerX = x + tileSize / 2;
        int centerY = y + tileSize / 2;
        int radius = tileSize / 3;

        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (i*i + j*j <= radius*radius) {
                    SDL_RenderDrawPoint(this->renderer, centerX + i, centerY + j);
                }
            }
        }

        // Draw border
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                int dist = i*i + j*j;
                if (dist <= radius*radius && dist >= (radius-1)*(radius-1)) {
                    SDL_RenderDrawPoint(this->renderer, centerX + i, centerY + j);
                }
            }
        }
    }
    else if (tile >= 'A' && tile <= 'Z') {
        // Monster - colored background with white letter
        setDrawColor(tileColor);
        drawRect(x + 2, y + 2, tileSize - 4, tileSize - 4, true);

        // Draw the letter using a simple 5x7 bitmap font
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int letterX = x + tileSize / 2 - 3;
        int letterY = y + tileSize / 2 - 4;

        // Simple character rendering - draw the letter
        // Using basic shapes to form letters A-Z

        // Draw letter outline (simplified - just draw the character as pixels)
        // For a simple approach, draw a 5x7 grid pattern for each letter
        // Here's a simplified version that draws vertical bars for all letters
        // and adds horizontal bars based on the letter

        // Vertical bars (most letters have these)
        for (int py = 0; py < 7; py++) {
            SDL_RenderDrawPoint(this->renderer, letterX, letterY + py);
            SDL_RenderDrawPoint(this->renderer, letterX + 4, letterY + py);
        }

        // Horizontal bars based on letter position
        for (int px = 1; px < 4; px++) {
            SDL_RenderDrawPoint(this->renderer, letterX + px, letterY);     // Top bar
            SDL_RenderDrawPoint(this->renderer, letterX + px, letterY + 3); // Middle bar
            SDL_RenderDrawPoint(this->renderer, letterX + px, letterY + 6); // Bottom bar
        }
    }
    else if (tile == EMPTY) {
        // Empty tile - dark background (already drawn)
    }

    // Draw grid lines
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
    drawRect(x, y, tileSize, tileSize, false);
}

void Renderer::drawBoard(Board& board, Player& player) {
    int camX = player.getPos().first;
    int camY = player.getPos().second;

    // Draw tiles: Y controls screen rows (vertical), X controls columns (horizontal)
    int screenY = 0;
    for (int x = camX - viewSizeX; x <= camX + viewSizeX; x++) {
        int screenX = 0;
        for (int y = camY - viewSizeY; y <= camY + viewSizeY; y++) {
            if (board.isValidTile(std::make_pair(x, y))) {
                char tile = board.getTile(std::make_pair(x, y));
                Color color = board.getColor(std::make_pair(x, y));
                drawTile(std::make_pair(x, y), tile, color, screenX, screenY);
            } else {
                // Out of bounds - draw black
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                drawRect(screenX * tileSize, screenY * tileSize, tileSize, tileSize, true);
            }
            screenX++;
        }
        screenY++;
    }
}

void Renderer::drawUI(Player& player) {
    // Draw UI panel at the bottom
    int uiY = (viewSizeY * 2 + 1) * tileSize + 10;
    int uiHeight = screenHeight - uiY;

    // Background for UI
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
    drawRect(0, uiY, screenWidth, uiHeight, true);

    // HP Bar
    int barWidth = 400;
    int barHeight = 30;
    int barX = 20;
    int barY = uiY + 10;

    // HP bar background
    SDL_SetRenderDrawColor(renderer, 60, 60, 70, 255);
    drawRect(barX, barY, barWidth, barHeight, true);

    // HP bar fill
    float hpPercent = static_cast<float>(player.getHP()) / player.getMAXHP();
    int fillWidth = static_cast<int>(barWidth * hpPercent);

    if (hpPercent > 0.6f) {
        SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
    } else if (hpPercent > 0.3f) {
        SDL_SetRenderDrawColor(renderer, 255, 200, 50, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    }
    drawRect(barX, barY, fillWidth, barHeight, true);

    // HP bar border
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    drawRect(barX, barY, barWidth, barHeight, false);

    // Display messages
    const int MAX_MESSAGES = 3;

    // Keep only recent messages to prevent unbounded growth
    if(msg_buffer.size() > MAX_MESSAGES * 2) {
        msg_buffer.erase(msg_buffer.begin(), msg_buffer.begin() + (msg_buffer.size() - MAX_MESSAGES));
    }

    // Note: For simple text rendering without SDL_ttf, we'll just display message count
    // To properly render text, you'd need SDL_ttf library
    // For now, messages are tracked but not visually rendered

    if(!player.isAlive()) {
        // Game over screen
        // Semi-transparent dark overlay
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
        drawRect(0, 0, screenWidth, screenHeight, true);

        // Red background box
        SDL_SetRenderDrawColor(renderer, 180, 30, 30, 255);
        drawRect(screenWidth/2 - 250, screenHeight/2 - 60, 500, 120, true);

        // Border
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        drawRect(screenWidth/2 - 250, screenHeight/2 - 60, 500, 120, false);

        // Draw "GAME OVER" text using large pixels
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        int textX = screenWidth/2 - 140;
        int textY = screenHeight/2 - 30;
        int pixelSize = 4;

        // G
        for (int y = 0; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 10; x++) drawRect(textX + x*pixelSize, textY, pixelSize, pixelSize, true);
        for (int x = 0; x < 10; x++) drawRect(textX + x*pixelSize, textY + 11*pixelSize, pixelSize, pixelSize, true);
        for (int y = 6; y < 12; y++) drawRect(textX + 9*pixelSize, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 5; x < 10; x++) drawRect(textX + x*pixelSize, textY + 6*pixelSize, pixelSize, pixelSize, true);

        textX += 55;
        // A
        for (int y = 2; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int y = 2; y < 12; y++) drawRect(textX + 8*pixelSize, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 9; x++) drawRect(textX + x*pixelSize, textY + 2*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 9; x++) drawRect(textX + x*pixelSize, textY + 6*pixelSize, pixelSize, pixelSize, true);

        textX += 55;
        // M
        for (int y = 0; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int y = 0; y < 12; y++) drawRect(textX + 10*pixelSize, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 5; x++) drawRect(textX + x*pixelSize, textY + x*pixelSize, pixelSize, pixelSize, true);
        for (int x = 6; x < 11; x++) drawRect(textX + x*pixelSize, textY + (10-x)*pixelSize, pixelSize, pixelSize, true);

        textX += 60;
        // E
        for (int y = 0; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 9; x++) drawRect(textX + x*pixelSize, textY, pixelSize, pixelSize, true);
        for (int x = 0; x < 8; x++) drawRect(textX + x*pixelSize, textY + 6*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 9; x++) drawRect(textX + x*pixelSize, textY + 11*pixelSize, pixelSize, pixelSize, true);

        textX += 70;
        // O
        for (int y = 0; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int y = 0; y < 12; y++) drawRect(textX + 9*pixelSize, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 10; x++) drawRect(textX + x*pixelSize, textY, pixelSize, pixelSize, true);
        for (int x = 0; x < 10; x++) drawRect(textX + x*pixelSize, textY + 11*pixelSize, pixelSize, pixelSize, true);

        textX += 55;
        // V
        for (int y = 0; y < 10; y++) drawRect(textX + y*pixelSize/2, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int y = 0; y < 10; y++) drawRect(textX + (18-y)*pixelSize/2, textY + y*pixelSize, pixelSize, pixelSize, true);
        drawRect(textX + 4*pixelSize, textY + 10*pixelSize, pixelSize, pixelSize, true);
        drawRect(textX + 4*pixelSize, textY + 11*pixelSize, pixelSize, pixelSize, true);

        textX += 55;
        // E
        for (int y = 0; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 9; x++) drawRect(textX + x*pixelSize, textY, pixelSize, pixelSize, true);
        for (int x = 0; x < 8; x++) drawRect(textX + x*pixelSize, textY + 6*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 9; x++) drawRect(textX + x*pixelSize, textY + 11*pixelSize, pixelSize, pixelSize, true);

        textX += 55;
        // R
        for (int y = 0; y < 12; y++) drawRect(textX, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int x = 0; x < 8; x++) drawRect(textX + x*pixelSize, textY, pixelSize, pixelSize, true);
        for (int x = 0; x < 8; x++) drawRect(textX + x*pixelSize, textY + 6*pixelSize, pixelSize, pixelSize, true);
        for (int y = 0; y < 6; y++) drawRect(textX + 8*pixelSize, textY + y*pixelSize, pixelSize, pixelSize, true);
        for (int y = 6; y < 12; y++) drawRect(textX + (y-2)*pixelSize, textY + y*pixelSize, pixelSize, pixelSize, true);
    }
}

void Renderer::draw(Game& game) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw game board
    drawBoard(game.getBoard(), game.getPlayer());

    // Draw UI
    drawUI(game.getPlayer());

    // Present
    SDL_RenderPresent(renderer);
}

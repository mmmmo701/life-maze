#include "Renderer.h"
#include "Board.h"

const std::string BLACK = "\033[0;37m";

std::string getColorCode(Color color) {
    if(color == Color::RED)
        return "\033[31m";
    else if(color == Color::BLUE)
        return "\033[34m";
    else if(color == Color::YELLOW)
        return "\033[33m";
    else if(color == Color::MAGNENTA)
        return "\033[35m";
    else
        return "";
}

Renderer::Renderer() {}

// drawTile now reads from board.getTile and prints it. Coloring for player/monster
// can still be applied by checking character, but since board stores the
// characters we mostly print them directly.
void Renderer::drawTile(std::pair<int,int> pos, Board& board) {
    Color color = board.getColor(pos);
    std::string colorCode = getColorCode(color);
    std::cout << colorCode;
    char c = board.getTile(pos);
    std::cout << c;
    if(colorCode != "")
        std::cout << "\033[0m";
}

void screenRefresh() {
    // Clear the console screen for windows and linux/macOS
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen and move cursor to top-left
}

void Renderer::drawBoard(Board& board, Player& player) {
    // Center camera on player's position but draw from the board grid.
    int camX = player.getPos().first;
    int camY = player.getPos().second;
    int viewSizeX = 12; 
    int viewSizeY = 20;
    for(int x = camX - viewSizeX; x <= camX + viewSizeX; x++) {
        for(int y = camY - viewSizeY; y <= camY + viewSizeY; y++) {
            if(board.isValidTile(std::make_pair(x,y)))
                drawTile(std::make_pair(x,y), board);
            else
                std::cout << ' '; 
        }
        std::cout << std::endl;
    }
}

void Renderer::drawUI(Player& player) {
    // For HP, etc.
    std::cout<<"HP: " << player.getHP() << "/" << player.getMAXHP() << std::endl;
    while(!msg_buffer.empty()) {
        std::cout << msg_buffer.front() << std::endl;
        msg_buffer.erase(msg_buffer.begin());
    }

    if(!player.isAlive()) {
        std::cout << "GAME OVER!" << std::endl;
        abort();
    }
}

void Renderer::draw(Game& game) {
    screenRefresh();
    drawBoard(game.getBoard(), game.getPlayer());
    drawUI(game.getPlayer());
}
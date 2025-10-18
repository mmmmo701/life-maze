#include "Renderer.h"

const std::string BLACK = "\033[0;30m";

std::string getColorCodeForHP(int hp, int maxHp) {
    if(hp > maxHp * 0.5) {
        return "\033[1;34m"; // Blue
    } else if(hp > maxHp * 0.2) {
        return "\033[1;33m"; // Yellow
    } else {
        return "\033[1;31m"; // Red
    }
}

Renderer::Renderer() {}

void Renderer::drawPlayer(Player& player) {
    std::string colorCode = getColorCodeForHP(player.getHP(), player.getMAXHP());
    std::cout << colorCode << player.getSymbol() << BLACK;
}

void Renderer::drawMonster(Monster& monster) {
    std::cout << "\033[1;31m" << monster.getSymbol() << BLACK; // Red for monsters
}

void Renderer::drawTile(int x, int y, Board& board, Player& player, std::vector<Monster>& monsters) {
    for(int i = 0; i < (int)(monsters.size()); i++) {
        if(monsters[i].getX() == x && monsters[i].getY() == y && monsters[i].isAlive()) {
            drawMonster(monsters[i]);
            return;
        }
    }
    if(player.getX() == x && player.getY() == y) {
        drawPlayer(player);
        return;
    }
    std::cout << board.getTile(x, y);
}

void screenRefresh() {
    // Clear the console screen for windows and linux/macOS
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen and move cursor to top-left
}

void Renderer::drawBoard(Board& board, Player& player, std::vector<Monster>& monsters) {
    
    int camX = player.getX();
    int camY = player.getY();
    int viewSizeX = 12; 
    int viewSizeY = 20;
    for(int x = camX - viewSizeX; x <= camX + viewSizeX; x++) {
        for(int y = camY - viewSizeY; y <= camY + viewSizeY; y++) {
            if(board.isValidTile(x, y))
                drawTile(x, y, board, player, monsters);
            else
                std::cout << ' '; 
        }
        std::cout << std::endl;
    }
}

void Renderer::drawUI(Player& player) {
    // For HP, etc.
    std::cout<<"HP: " << player.getHP() << "/" << player.getMAXHP() << std::endl;
    if(!player.isAlive()) {
        std::cout << "GAME OVER!" << std::endl;
    }
}

void Renderer::draw(Game& game) {
    screenRefresh();
    drawBoard(game.getBoard(), game.getPlayer(), game.getMonsters());
    drawUI(game.getPlayer());
}
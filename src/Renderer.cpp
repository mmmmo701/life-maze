#include "Renderer.h"
#include "Game.h"
#include <iostream>

Renderer::Renderer() {}

void Renderer::draw(Game& game) {
    drawBoard(game.getBoard(), game.getPlayer());
    drawUI(game.getPlayer());
}

void Renderer::drawBoard(Board& board, Player& player) {
    // refresh the screen first (system dependent)
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    // then draw the board centered on the player
    // Your camera logic from displayBoard() goes here.
    int camX = player.getX();
    int camY = player.getY();
    int viewSizeX = 12; 
    int viewSizeY = 20;
    for(int x = camX - viewSizeX; x <= camX + viewSizeX; x++) {
        for(int y = camY - viewSizeY; y <= camY + viewSizeY; y++) {
            if(board.isValidTile(x, y)) {
                if(x == player.getX() && y == player.getY()) {
                    std::cout << player.getSymbol(); // Draw the player
                } else {
                    std::cout << board.getTile(x, y); // Draw the board tile
                }
            } else {
                std::cout << ' '; // Out of bounds
            }
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
#include "Renderer.h"
#include "Game.h"
#include <iostream>

void draw(const Game& game) const {
    drawBoard(game.getBoard(), game.getPlayer());
    drawUI(game.getPlayer());
}

void drawBoard(const Board& board, const Player& player) const {
    // Your camera logic from displayBoard() goes here.
    int size = board.getSize();
    int camX = player.getX();
    int camY = player.getY();
    int viewSize = 10; // How far the camera can see in each direction.
    for(int y = camY - viewSize; y <= camY + viewSize; y++) {
        for(int x = camX - viewSize; x <= camX + viewSize; x++) {
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

void drawUI(const Player& player) const {
    // For HP, etc.
    cout<<"HP: " << player.getHP() << "/" << Player::MAX_HP << std::endl;
    if(!player.isAlive()) {
        std::cout << "GAME OVER!" << std::endl;
    }
}
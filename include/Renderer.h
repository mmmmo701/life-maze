#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"
#include <iostream>
#include <string>
#include <utility>

class Renderer {
public:
    Renderer();
    
    // Takes a constant reference to the Game object to ensure it cannot modify it.
    void draw(Game& game);

private:
    // Your camera logic from displayBoard() goes here.
    // drawBoard now renders directly from the board grid (board.getTile).
    void drawBoard(Board& board, Player& player);
    void drawUI(Player& player); // For HP, etc.
    void drawPlayer(Player& player);
    void drawMonster(Monster& monster);
    void drawTile(std::pair<int,int> pos, Board& board);
};

#endif //RENDERER_H
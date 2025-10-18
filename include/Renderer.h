#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h"
#include <iostream>
#include <string>

class Renderer {
public:
    Renderer();
    
    // Takes a constant reference to the Game object to ensure it cannot modify it.
    void draw(Game& game);

private:
    // Your camera logic from displayBoard() goes here.
    void drawBoard(Board& board, Player& player, std::vector<Monster>& monsters);
    void drawUI(Player& player); // For HP, etc.
    void drawPlayer(Player& player);
    void drawMonster(Monster& monster);
    void drawTile(int x, int y, Board& board, Player& player, std::vector<Monster>& monsters);
};

#endif //RENDERER_H
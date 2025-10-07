#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h" // Needs to know about the game to draw it.

class Renderer {
public:
    Renderer();
    
    // Takes a constant reference to the Game object to ensure it cannot modify it.
    void draw(Game& game);

private:
    // Your camera logic from displayBoard() goes here.
    void drawBoard(Board& board, Player& player);
    void drawUI(Player& player); // For HP, etc.
};

#endif //RENDERER_H
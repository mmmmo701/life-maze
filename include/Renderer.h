#ifndef RENDERER_H
#define RENDERER_H

#include "Game.h" // Needs to know about the game to draw it.

class Renderer {
public:
    Renderer();
    
    // Takes a constant reference to the Game object to ensure it cannot modify it.
    void draw(const Game& game) const;

private:
    // Your camera logic from displayBoard() goes here.
    void drawBoard(const Board& board, const Player& player) const;
    void drawUI(const Player& player) const; // For HP, etc.
};

#endif //RENDERER_H
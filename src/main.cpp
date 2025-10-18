#include "Game.h"
#include "Renderer.h"
#include "sys-getch.h"
#include <cstdio>
#include <iostream>

// This function translates raw characters into game commands.
Direction getDirectionFromInput() {
    char input;
    // use sys-getch.h for non-blocking single character input
    while (true) {
        if (_kbhit()) {
            input = _getch();
            break;
        }   
    }
    fflush(stdin); // Clear the input buffer
    switch (input) {
        case 'w': return Direction::UP;
        case 'a': return Direction::LEFT;
        case 's': return Direction::DOWN;
        case 'd': return Direction::RIGHT;
        default:  return getDirectionFromInput(); // Simple way to handle bad input
    }
}

int main() {
    Game game;
    Renderer renderer;
    
    while (!game.isGameOver()) {
        renderer.draw(game);
        Direction nextMove = getDirectionFromInput();
        game.update(nextMove);
    }
    
    std::cout << "Game Over!" << std::endl;
    
    return 0;
}
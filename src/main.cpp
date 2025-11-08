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
            // Validate input immediately, loop instead of recursion
            if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                break;
            }
            // Invalid input - continue waiting for valid key
        }
    }
    // No need to flush stdin with _getch() - it reads single char directly
    switch (input) {
        case 'w': return Direction::UP;
        case 'a': return Direction::LEFT;
        case 's': return Direction::DOWN;
        case 'd': return Direction::RIGHT;
        default:  return Direction::UP; // Should never reach here due to validation above
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
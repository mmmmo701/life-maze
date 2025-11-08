#include "Game.h"
#include "Renderer.h"
#include <SDL2/SDL.h>
#include <iostream>

int main() {
    Game game;
    Renderer renderer;

    // Initialize SDL renderer
    if (!renderer.init("Life Maze", 1280, 720)) {
        std::cerr << "Failed to initialize renderer!" << std::endl;
        return 1;
    }

    bool running = true;
    bool needsUpdate = false;
    Direction nextMove = Direction::UP;

    // Main game loop
    while (running && !game.isGameOver()) {
        SDL_Event event;

        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                needsUpdate = true;
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_UP:
                        nextMove = Direction::UP;
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        nextMove = Direction::LEFT;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        nextMove = Direction::DOWN;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        nextMove = Direction::RIGHT;
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    default:
                        needsUpdate = false;
                        break;
                }
            }
        }

        // Update game state if a move was made
        if (needsUpdate) {
            game.update(nextMove);
            needsUpdate = false;
        }

        // Render
        renderer.draw(game);

        // Small delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    if (game.isGameOver()) {
        std::cout << "Game Over! Final render..." << std::endl;
        renderer.draw(game);
        SDL_Delay(3000); // Show game over screen for 3 seconds
    }

    renderer.cleanup();
    return 0;
}
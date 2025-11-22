#include "Game.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
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

    // previous-frame key state for edge detection
    bool prevW = false, prevA = false, prevS = false, prevD = false;
    bool prevUp = false, prevLeft = false, prevDown = false, prevRight = false;
    bool prevEsc = false;

    // Main game loop
    while (running && !game.isGameOver()) {
        SDL_Event event;

        // Handle events (keep quit handling; avoid direct keyboard-event field access)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            // ...other events if needed...
        }

        // Poll keyboard state and detect edge presses (single move per key press)
        int numKeys;
        const bool* kb = SDL_GetKeyboardState(&numKeys);

        bool curW = kb[SDL_SCANCODE_W];
        bool curA = kb[SDL_SCANCODE_A];
        bool curS = kb[SDL_SCANCODE_S];
        bool curD = kb[SDL_SCANCODE_D];
        bool curUp = kb[SDL_SCANCODE_UP];
        bool curLeft = kb[SDL_SCANCODE_LEFT];
        bool curDown = kb[SDL_SCANCODE_DOWN];
        bool curRight = kb[SDL_SCANCODE_RIGHT];
        bool curEsc = kb[SDL_SCANCODE_ESCAPE];

        if ((curW && !prevW) || (curUp && !prevUp)) {
            nextMove = Direction::UP;
            needsUpdate = true;
        } else if ((curA && !prevA) || (curLeft && !prevLeft)) {
            nextMove = Direction::LEFT;
            needsUpdate = true;
        } else if ((curS && !prevS) || (curDown && !prevDown)) {
            nextMove = Direction::DOWN;
            needsUpdate = true;
        } else if ((curD && !prevD) || (curRight && !prevRight)) {
            nextMove = Direction::RIGHT;
            needsUpdate = true;
        }

        if (curEsc && !prevEsc) {
            running = false;
        }

        // update previous state
        prevW = curW; prevA = curA; prevS = curS; prevD = curD;
        prevUp = curUp; prevLeft = curLeft; prevDown = curDown; prevRight = curRight;
        prevEsc = curEsc;

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
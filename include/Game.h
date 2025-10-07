#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"

// Using an enum for directions is much clearer than 0, 1, 2, 3.
enum class Direction { UP, DOWN, LEFT, RIGHT };
const int DIRDX[4] = {-1,1,0,0};
const int DIRDY[4] = {0,0,-1,1};

class Game {
public:
    Game();

    // The main update function. It takes a player action and updates the game state.
    void update(Direction dir);

    // Functions to provide game state to the outside world (like the Renderer).
    Player& getPlayer();
    Board& getBoard();
    bool isGameOver();

private:
    Player player;
    Board board;

    // A private helper function to handle movement logic.
    void processMovement(Direction dir);
    void addRandomObstacle();
};

#endif //GAME_H

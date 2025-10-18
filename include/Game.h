#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "Monster.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

// Using an enum for directions is much clearer than 0, 1, 2, 3.
enum class Direction { UP, DOWN, LEFT, RIGHT };
const int DIRDX[4] = {-1,1,0,0};
const int DIRDY[4] = {0,0,-1,1};

class Game {
public:
    Game();
    void update(Direction dir);
    Player& getPlayer();
    Board& getBoard();
    bool isGameOver();
    void removeDeadMonsters();
    std::vector<Monster>& getMonsters() { return monsters; }

private:
    Player player;
    Board board;
    int round;
    std::vector<Monster> monsters;

    void spawnMonster();
    void processMovement(Direction dir);
    void addRandomObstacle();

};

#endif //GAME_H

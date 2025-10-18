#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "Monster.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };
extern const int DIRDX[4];
extern const int DIRDY[4];
extern std::vector<std::string> msg_buffer;

class Game {
public:
    Game();
    void update(Direction dir);
    Player& getPlayer();
    Board& getBoard();
    bool isGameOver();
    void updateMonster();
    void moveMonster(Monster* monster);
    int monsterAttack(Monster* monster);
    bool haveElements(int x, int y);
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

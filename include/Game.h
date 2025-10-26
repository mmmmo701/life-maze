#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"
#include "Monster.h"
#include <string>
#include <utility>

enum class Direction { UP, DOWN, LEFT, RIGHT };
extern const int DIRDX[4];
extern const int DIRDY[4];
extern std::vector<std::string> msg_buffer;

class Game {
public:
    // game logics
    Game();
    void update(Direction dir);
    Player& getPlayer();
    Board& getBoard();
    bool isGameOver();

    // monsters
    std::vector<Monster>& getMonsters() { return monsters; }
    void updateMonster();
    std::pair<int,int>  getMoveMonsterDir(Monster* monster);
    void moveMonster(Monster* monster);
    int monsterAttack(Monster* monster);

    // obstacles: occupancy tracked on Board tiles. Use board.getTile / isWalkable.

private:
    Board board;
    Player player;
    int round;
    std::vector<Monster> monsters;

    void spawnMonster();
    void processMovement(Direction dir);
    void addRandomObstacle();

};

#endif //GAME_H

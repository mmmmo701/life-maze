#ifndef MONSTER_H
#define MONSTER_H

#include "Player.h"
#include "Board.h"
#include <algorithm>
#include <iostream>

class Monster {
public:
    Monster(int level, int startX, int startY);
    ~Monster() = default;
    int attack(Player& player);
    int getHealth() const;
    void takeDamage(int amount);

    char getSymbol() const { return symbol; }
    bool isAlive() const { return health > 0; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    void moveTowardsPlayer(Player& player, Board& board);

private:
    int level;
    int health;
    int attackPower;
    char symbol;
    int x = 0, y = 0; 

    void move(Player & player, Board& board);
};

#endif // MONSTER_H
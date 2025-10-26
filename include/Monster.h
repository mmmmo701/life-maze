#ifndef MONSTER_H
#define MONSTER_H

#include <vector>

class Monster {
public:
    Monster(int level, int startX, int startY);
    ~Monster() = default;
    int getHealth() const;
    int getATK() const;
    void takeDamage(int amount);

    char getSymbol() const { return symbol; }
    bool isAlive() const { return health > 0; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    std::pair<int,int> dirToward(int tarX, int tarY);
    std::pair<int,int> newPosByDir(std::pair<int,int> dir);
    void move(int dx, int dy) { x += dx; y += dy; }

private:
    int level;
    int health;
    int attackPower;
    char symbol;
    int x = 0, y = 0; 
};

#endif // MONSTER_H
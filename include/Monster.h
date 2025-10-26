#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <utility>

class Monster {
public:
    Monster(int level, std::pair<int,int> startPos);
    ~Monster() = default;
    int getHealth() const;
    int getATK() const;
    void takeDamage(int amount);

    char getSymbol() const { return symbol; }
    bool isAlive() const { return health > 0; }
    std::pair<int,int> getPos() const { return pos; }
    void setPosition(std::pair<int,int> newPos) { pos = newPos; }
    std::pair<int,int> dirToward(std::pair<int,int> tar);
    std::pair<int,int> newPosByDir(std::pair<int,int> dir);
    void move(std::pair<int,int> delta) { pos.first += delta.first; pos.second += delta.second; }

private:
    int level;
    int health;
    int attackPower;
    char symbol;
    std::pair<int,int> pos = {0,0}; 
};

#endif // MONSTER_H
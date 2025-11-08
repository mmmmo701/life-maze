// implementation of Monster class

#include "Monster.h"
#include <iostream>
#include <vector>
#include <algorithm>

Monster::Monster(int level, std::pair<int,int> startPos)
    : level(level), pos(startPos) {
    health = 100 + (level - 1) * 20;
    attackPower = 10 + (level - 1) * 5;
    // Prevent symbol overflow: wrap around after 'Z' or use modulo
    // Supports up to 26 levels (A-Z), then wraps around
    symbol = 'A' + ((level - 1) % 26);
}

int Monster::getHealth() const {
    return health;
}

int Monster::getATK() const {
    return attackPower;
}

void Monster::takeDamage(int amount) {
    health = std::max(0, health - amount);
}

std::pair<int,int> Monster::dirToward(std::pair<int,int> tar) {
    int dx = (tar.first > pos.first) ? 1 : (tar.first < pos.first) ? -1 : 0;
    int dy = (tar.second > pos.second) ? 1 : (tar.second < pos.second) ? -1 : 0;
    return std::make_pair(dx, dy);
}

std::pair<int,int> Monster::newPosByDir(std::pair<int,int> dir) {
    return std::make_pair(pos.first + dir.first, pos.second + dir.second);
}

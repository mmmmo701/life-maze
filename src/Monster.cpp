// implementation of Monster class

#include "Monster.h"

Monster::Monster(int level, int startX, int startY) 
    : level(level), x(startX), y(startY) {
    health = 100 + (level - 1) * 20;
    attackPower = 10 + (level - 1) * 5;
    symbol = 'A' + (level - 1); // Different symbol per level
}

int Monster::getHealth() const {
    return health;
}

void Monster::takeDamage(int amount) {
    health = std::max(0, health - amount);
}

std::pair<int,int> Monster::dirToward(int tarX, int tarY) {
    int dx = (tarX > x) ? 1 : (tarX < x) ? -1 : 0;
    int dy = (tarY > y) ? 1 : (tarY < y) ? -1 : 0;
    return std::make_pair(dx, dy);
}

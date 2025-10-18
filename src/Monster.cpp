// implementation of Monster class

#include "Monster.h"

Monster::Monster(int level, int startX, int startY) 
    : level(level), x(startX), y(startY) {
    health = 100 + (level - 1) * 20;
    attackPower = 10 + (level - 1) * 5;
    symbol = 'A' + (level - 1); // Different symbol per level
}

int Monster::attack(Player& player) {
    int damage = attackPower;
    player.takeDamage(damage);
    return damage;
}

int Monster::getHealth() const {
    return health;
}

void Monster::takeDamage(int amount) {
    health = std::max(0, health - amount);
}

void Monster::move(Player& player, Board& board) {
    int playerX = player.getX();
    int playerY = player.getY();
    if(x < playerX && board.isWalkable(x+1,y)) 
        x++;
    else if(x > playerX && board.isWalkable(x,y+1)) 
        x--;
    if(y < playerY && board.isWalkable(x,y+1))
        y++;
    else if(y > playerY && board.isWalkable(x,y-1)) 
        y--;
}

void Monster::moveTowardsPlayer(Player& player, Board& board) {
    int distanceX = std::abs(player.getX() - x);
    int distanceY = std::abs(player.getY() - y);
    if(distanceX + distanceY == 1) {
        attack(player);
    } else {
        move(player, board);
    }
}

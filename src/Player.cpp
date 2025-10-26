#include "Player.h"

Player::Player(std::pair<int,int> startPos) : pos(startPos), hp(MAX_HP), atk(20) {}

void Player::move(std::pair<int,int> delta) {
    pos.first += delta.first;
    pos.second += delta.second;
}

void Player::takeDamage(int amount) {
    hp -= amount;
}

bool Player::isAlive() const {
    return hp > 0;
}

char Player::getSymbol() const {
    return '@';
}

std::pair<int,int> Player::getPos() const {
    return pos;
}

int Player::getHP() const {
    return hp;
}

int Player::getMAXHP() const {
    return MAX_HP;
}

int Player::getATK() const {
    return atk;
}
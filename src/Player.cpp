#include "Player.h"
#include <iostream>

Player::Player(int startX, int startY) : x(startX), y(startY), hp(MAX_HP) {}

void Player::move(int dx, int dy) {
    x += dx;
    y += dy;
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

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

int Player::getHP() const {
    return hp;
}

int Player::getMAXHP() const {
    return MAX_HP;
}
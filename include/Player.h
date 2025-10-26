#ifndef PLAYER_H
#define PLAYER_H

#include <utility>

class Player {
public:
    // Constructor to initialize the player at a starting position.
    Player(std::pair<int,int> startPos);

    // Move by a delta (dx,dy)
    void move(std::pair<int,int> delta);
    void takeDamage(int amount);

    // Position accessor
    std::pair<int,int> getPos() const;

    int getHP() const; int getMAXHP() const;
    int getATK() const;
    char getSymbol() const;
    bool isAlive() const;

private:
    std::pair<int,int> pos;
    int hp, atk;
    static const int MAX_HP = 1000;
};

#endif //PLAYER_H

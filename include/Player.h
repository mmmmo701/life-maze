#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    // Constructor to initialize the player at a starting position.
    Player(int startX, int startY);

    void move(int dx, int dy);
    void takeDamage(int amount);

    int getX() const; int getY() const; 
    int getHP() const; int getMAXHP() const;
    int getATK() const;
    char getSymbol() const;
    bool isAlive() const;

private:
    int x, y;
    int hp, atk;
    static const int MAX_HP = 1000;
};

#endif //PLAYER_H

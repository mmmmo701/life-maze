#include "Game.h"
#include <iostream>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

std::vector<std::string> msg_buffer;
const int DIRDX[4] = {-1,1,0,0};
const int DIRDY[4] = {0,0,-1,1};

Game::Game() : player(board.getBOARD_SIZE() / 2, board.getBOARD_SIZE() / 2), board(), round(1) {}

Player& Game::getPlayer() { return player; }

Board& Game::getBoard() { return board; }

bool Game::isGameOver() { return !player.isAlive(); }
 
/*
 * return 0 if no obstacles
 * return 1~monsters.size() if there is a monster in the position
 * return monsters.size() + 1 if there is player
 * return monsters.size() + 2 if there is a wall
 */
int Game::haveElements(int x, int y) {
    if(!board.isWalkable(x,y))
        return (int)(monsters.size()) + 2;
    for(int i=0; i < (int)(monsters.size()); i++) {
        if(monsters[i].getX() == x && monsters[i].getY() == y && monsters[i].isAlive()) {
            return i+1;
        }
    }
    if(player.getX() == x && player.getY() == y)
        return (int)(monsters.size()) + 1;
    return 0;
}

void Game::processMovement(Direction dir) {
    int dirInt = static_cast<int>(dir);
    int newPlayerX = player.getX() + DIRDX[dirInt];
    int newPlayerY = player.getY() + DIRDY[dirInt];
    int he = haveElements(newPlayerX, newPlayerY);
    if(!he)
        player.move(DIRDX[dirInt], DIRDY[dirInt]);
    else if(1 <= he && he <= (int)(monsters.size())) {
        int mpos = he - 1;
        monsters[mpos].takeDamage(player.getATK());
        std::string s;
        s.push_back(monsters[mpos].getSymbol());
        msg_buffer.push_back("Player attacked monster " + s + " for " + std::to_string(player.getATK()) + " damage!");
        msg_buffer.push_back("Monster " + s + "'s remaining HP: " + std::to_string(monsters[mpos].getHealth()));
    }
}

int getNMonstersForRound(int round) {
    return static_cast<int>(log(round / 20)) + 2;
}

int getLevelRound(int round) {
    int level = (round / 100) + 1;
    if(rand() % 100 < 20) 
        level++;
    if(rand() % 100 < 5) 
        level++;
    if(rand() % 100 < 1 && level > 1) 
        level--;
    return level;
}

int dist(int x, int y, Player& player) {
    return abs(x - player.getX()) + abs(y - player.getY());
}

bool tooClose(int x,int y,Player& player) {
    return dist(x, y, player) < 10;
}

int distToProb(int dist) {
    return 400 / (dist + 19) + 77;
}

void Game::spawnMonster() {
    if(round%20 == 0) {
        for(int i=0; i<getNMonstersForRound(round); i++) {
            int level = getLevelRound(round);
            int spawnX, spawnY;
            do {
                spawnX = rand() % board.getBOARD_SIZE();
                spawnY = rand() % board.getBOARD_SIZE();
                #ifdef DEBUG
                std::cout << spawnX << ' ' << spawnY << std::endl;
                #endif
            } while(haveElements(spawnX, spawnY) || tooClose(spawnX, spawnY, player));
            Monster x = Monster(level, spawnX, spawnY);
            monsters.push_back(x);
        }
    }
}

int Game::monsterAttack(Monster* monster) {
    int damage = monster->getATK();
    player.takeDamage(damage);
    return damage;
}

std::pair<int,int> Game::getMoveMonsterDir(Monster* monster) {
    std::pair<int,int> dir;
    std::pair<int,int> newPos;
    do {
        if(rand() % 100 <= distToProb(dist(monster->getX(), monster->getY(), player)))
            dir = monster->dirToward(player.getX(), player.getY());
        else {
            int dirID = rand() % 4;
            dir = std::make_pair(DIRDX[dirID], DIRDY[dirID]);
        }       
        newPos = monster->newPosByDir(dir);
    } while(!board.isValidTile(newPos.first, newPos.second));

    // if dir is unWalkable, get a new dir
    if(haveElements(newPos.first, newPos.second)) {
        int dirID = rand() % 4;
        dir = std::make_pair(DIRDX[dirID], DIRDY[dirID]);
    }
    return dir;
}

void Game::moveMonster(Monster* monster) {
    Player player = getPlayer();
    Board board = getBoard();

    std::pair<int,int> dir = getMoveMonsterDir(monster);
    std::pair<int,int> newPos = monster->newPosByDir(dir);

    if(!haveElements(newPos.first, newPos.second)) 
         monster->move(dir.first, dir.second);

    int distX = abs(monster->getX() - player.getX());
    int distY = abs(monster->getY() - player.getY());
    if(distX + distY <= 1) {
        int damage = monsterAttack(monster);
        std::string s;
        s.push_back(monster->getSymbol());
        msg_buffer.push_back("Monster " + s + " attacks player for " + std::to_string(damage) + " damage!");
    }
}

void Game::updateMonster() {
    for(int i=0; i < (int)(monsters.size()); i++) {
        if(monsters[i].isAlive())
            moveMonster(&monsters[i]);
        else {
            monsters.erase(monsters.begin() + i);
            #ifdef DEBUG
            std::cout<<"erased monster\n";
            #endif
        }
    }
}

void Game::update(Direction dir) {
    processMovement(dir);
    spawnMonster();
    updateMonster(); 
    round++;
}

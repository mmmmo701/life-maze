#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <cctype>

std::vector<std::string> msg_buffer;
const int DIRDX[4] = {-1,1,0,0};
const int DIRDY[4] = {0,0,-1,1};

Game::Game() : board(), player(std::make_pair(board.getBOARD_SIZE() / 2, board.getBOARD_SIZE() / 2)), round(1) {
    // Place player on the board
    board.setTile(player.getPos(), player.getSymbol(), Color::BLUE);
    monsters.clear();
    assert(monsters.size() == 0);
}

Player& Game::getPlayer() { return player; }

Board& Game::getBoard() { return board; }

bool Game::isGameOver() { return !player.isAlive(); }

int getNMonstersForRound(int round) {
    return static_cast<int>(log(std::max(1, round) / 20)) + 2;
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

int dist(std::pair<int,int> a, Player& player) {
    auto p = player.getPos();
    return abs(a.first - p.first) + abs(a.second - p.second);
}

bool tooClose(std::pair<int,int> a, Player& player) {
    return dist(a, player) < 10;
}

int distToProb(int d) {
    return 400 / (d + 19) + 77;
}

Color getPlayerColor(Player player) {
    if(player.getHP() >= 0.6 * player.getMAXHP())
        return Color::BLUE;
    else if(player.getHP() >= 0.3 * player.getMAXHP())
        return Color::YELLOW;
    else
        return Color::RED;
}

void Game::processMovement(Direction dir) {
    int dirInt = static_cast<int>(dir);
    std::pair<int,int> delta = std::make_pair(DIRDX[dirInt], DIRDY[dirInt]);
    std::pair<int,int> newPlayerPos = std::make_pair(player.getPos().first + delta.first, player.getPos().second + delta.second);

    if(!board.isValidTile(newPlayerPos)) return;

    char tile = board.getTile(newPlayerPos);
    if(tile == EMPTY) {
        // move player on the board
        board.setTile(player.getPos(), EMPTY, Color::DEFAULT);
        player.move(delta);
    } 
    else if(tile == '#') {
        // wall: do nothing
    } 
    else if(std::isalpha((unsigned char)tile)) {
        // tile occupied by a monster symbol: find monster and attack
        for(auto &m : monsters) {
            if(m.isAlive() && m.getPos() == newPlayerPos) {
                m.takeDamage(player.getATK());
                std::string s;
                s.push_back(m.getSymbol());
                msg_buffer.push_back("Player attacked monster " + s + " for " + std::to_string(player.getATK()) + " damage!");
                msg_buffer.push_back("Monster " + s + "'s remaining HP: " + std::to_string(m.getHealth()));
                // if monster died, clear tile
                if(!m.isAlive()) {
                    board.setTile(m.getPos(), EMPTY, Color::DEFAULT);
                }
                break;
            }
        }
    } 
    board.setTile(player.getPos(), player.getSymbol(), getPlayerColor(player));
}

void Game::spawnMonster() {
    if(round % 20 == 0) {
        int n = getNMonstersForRound(round);
        for(int i = 0; i < n; ++i) {
            int level = getLevelRound(round);
            std::pair<int,int> spawnPos;
            do {
                spawnPos.first = rand() % board.getBOARD_SIZE();
                spawnPos.second = rand() % board.getBOARD_SIZE();
            } while(board.getTile(spawnPos) != EMPTY || tooClose(spawnPos, player));
            Monster m = Monster(level, spawnPos);
            monsters.push_back(m);
            board.setTile(spawnPos, m.getSymbol(), Color::MAGNENTA);
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
        if(rand() % 100 <= distToProb(dist(monster->getPos(), player)))
            dir = monster->dirToward(player.getPos());
        else {
            int dirID = rand() % 4;
            dir = std::make_pair(DIRDX[dirID], DIRDY[dirID]);
        }
        newPos = monster->newPosByDir(dir);
    } while(!board.isValidTile(newPos));

    // if target tile is not walkable (occupied/wall), pick another random dir
    if(!board.isWalkable(newPos) && board.getTile(newPos) != player.getSymbol()) {
        int dirID = rand() % 4;
        dir = std::make_pair(DIRDX[dirID], DIRDY[dirID]);
    }
    return dir;
}

void Game::moveMonster(Monster* monster) {
    Player& p = getPlayer();

    std::pair<int,int> dir = getMoveMonsterDir(monster);
    std::pair<int,int> newPos = monster->newPosByDir(dir);

    if(board.isValidTile(newPos) && board.getTile(newPos) == EMPTY) {
        // move monster on board
        board.setTile(monster->getPos(), EMPTY, Color::DEFAULT);
        monster->move(dir);
        board.setTile(monster->getPos(), monster->getSymbol(), Color::MAGNENTA);
    } 
    else if(board.isValidTile(newPos) && board.getTile(newPos) == p.getSymbol()) {
        // monster moves into player -> attack
        int damage = monsterAttack(monster);
        std::string s;
        s.push_back(monster->getSymbol());
        msg_buffer.push_back("Monster " + s + " attacks player for " + std::to_string(damage) + " damage!");
        return;
    }

    // proximity attack if adjacent
    int distSum = abs(monster->getPos().first - p.getPos().first) + abs(monster->getPos().second - p.getPos().second);
    if(distSum <= 1) {
        int damage = monsterAttack(monster);
        std::string s;
        s.push_back(monster->getSymbol());
        msg_buffer.push_back("Monster " + s + " attacks player for " + std::to_string(damage) + " damage!");
    }
}

void Game::updateMonster() {
    for(int i = 0; i < (int)(monsters.size()); i++) {
        if(monsters[i].isAlive()) {
            moveMonster(&monsters[i]);
        } else {
            // clear tile on board and erase monster
            board.setTile(monsters[i].getPos(), EMPTY, Color::DEFAULT);
            monsters.erase(monsters.begin() + i);
            i--;
        }
    }
}

void Game::update(Direction dir) {
    spawnMonster();
    updateMonster();
    processMovement(dir);
    round++;
}

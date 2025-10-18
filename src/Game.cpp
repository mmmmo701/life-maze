#include "Game.h"

Game::Game() : player(board.getBOARD_SIZE() / 2, board.getBOARD_SIZE() / 2), board(), round(1) {}

Player& Game::getPlayer() {
    return player;
}

Board& Game::getBoard() {
    return board;
}

bool Game::isGameOver() {
    #ifdef DEBUG
    std::cout << "DEBUG: Checking if game is over. Player alive: " << player.isAlive() << std::endl;
    #endif
    return !player.isAlive();
}

void Game::processMovement(Direction dir) {
    int dirInt = static_cast<int>(dir);
    int newPlayerX = player.getX() + DIRDX[dirInt];
    int newPlayerY = player.getY() + DIRDY[dirInt];
    if(board.isValidTile(newPlayerX, newPlayerY) && board.isWalkable(newPlayerX, newPlayerY)) {
        player.move(DIRDX[dirInt], DIRDY[dirInt]);
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

bool tooClose(int x,int y,Player& player) {
    return abs(x - player.getX()) + abs(y - player.getY()) < 10;
}

void Game::spawnMonster() {
    if(round%20 == 0) {
        for(int i=0; i<getNMonstersForRound(round); i++) {
            int level = getLevelRound(round);
            int spawnX, spawnY;
            do {
                spawnX = rand() % board.getBOARD_SIZE();
                spawnY = rand() % board.getBOARD_SIZE();
            } while(!board.isWalkable(spawnX, spawnY) || tooClose(spawnX, spawnY, player));
            Monster x = Monster(level, spawnX, spawnY);
            monsters.push_back(x);
        }
    }
}

void Game::removeDeadMonsters() {
    for(int i=0; i < (int)(monsters.size()); i++)
        if(!monsters[i].isAlive())
            monsters.erase(monsters.begin() + i);
}


void Game::update(Direction dir) {
    processMovement(dir);
    spawnMonster();
    removeDeadMonsters();
    round++;
}

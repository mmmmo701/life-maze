#include "Game.h"

std::vector<std::string> msg_buffer;
const int DIRDX[4] = {-1,1,0,0};
const int DIRDY[4] = {0,0,-1,1};

Game::Game() : player(board.getBOARD_SIZE() / 2, board.getBOARD_SIZE() / 2), board(), round(1) {}

Player& Game::getPlayer() {
    return player;
}

Board& Game::getBoard() {
    return board;
}

bool Game::isGameOver() {
    return !player.isAlive();
}

bool Game::haveElements(int x, int y) {
    if(!board.isWalkable(x,y))
        return true;
    for(int i=0; i < (int)(monsters.size()); i++) {
        if(monsters[i].getX() == x && monsters[i].getY() == y && monsters[i].isAlive()) {
            return true;
        }
    }
    if(player.getX() == x && player.getY() == y) {
        return true;
    }
    return false;
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
            } while(haveElements(spawnX, spawnY) || tooClose(spawnX, spawnY, player));
            Monster x = Monster(level, spawnX, spawnY);
            monsters.push_back(x);
        }
    }
}

int Game::monsterAttack(Monster* monster) {
    int damage = 10 + (monster->getHealth() / 10);
    player.takeDamage(damage);
    return damage;
}

void Game::moveMonster(Monster* monster) {
    Player player = getPlayer();
    Board board = getBoard();

    std::pair<int,int> dir = monster->dirToward(player.getX(), player.getY());
    int newX = monster->getX() + dir.first;
    int newY = monster->getY() + dir.second;
    if(!haveElements(newX, newY)) 
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
        if(!monsters[i].isAlive())
            monsters.erase(monsters.begin() + i);
    }
}

void Game::update(Direction dir) {
    processMovement(dir);
    spawnMonster();
    updateMonster(); 
    round++;
}

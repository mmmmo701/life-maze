#include "Game.h"
#include <cstdlib>

const Player& Game::getPlayer() const {
    return player;
}

const Board& Game::getBoard() const {
    return board;
}

bool Game::isGameOver() const {
    return player.isAlive();
}

void Game::processMovement(Direction dir) {
    int newPlayerX = player.getX() + DIRDX[dir];
    int newPlayerY = player.getY() + DIRDY[dir];
    if(board.isWalkable(newPlayerX, newPlayerY) && board.isPositionValid(newPlayerX, newPlayerY)) {
        player.move(DIRDX[dir], DIRDY[dir]);
    }
}

void Game::addRandomObstacle() {
    int obsX = 0, obsY = 0;
    do {
        obsX = rand() % board.BOARD_SIZE;
        obsY = rand() % board.BOARD_SIZE;
    } while(!board.isWalkable());
    board.setTile(obsX, obsY, '#');
}

void Game::update(Direction dir) {
    processMovement(dir);
    addRandomObstacle();
}

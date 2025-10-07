#include "Game.h"
#include <cstdlib>

Game::Game() : player(board.BOARD_SIZE / 2, board.BOARD_SIZE / 2), board() {}

Player& Game::getPlayer() {
    return player;
}

Board& Game::getBoard() {
    return board;
}

bool Game::isGameOver() {
    return player.isAlive();
}

void Game::processMovement(Direction dir) {
    int dirInt = static_cast<int>(dir);
    int newPlayerX = player.getX() + DIRDX[dirInt];
    int newPlayerY = player.getY() + DIRDY[dirInt];
    if(board.isValidTile(newPlayerX, newPlayerY) && board.isWalkable(newPlayerX, newPlayerY)) {
        player.move(DIRDX[dirInt], DIRDY[dirInt]);
    }
}

void Game::addRandomObstacle() {
    int obsX = 0, obsY = 0;
    do {
        obsX = rand() % board.BOARD_SIZE;
        obsY = rand() % board.BOARD_SIZE;
    } while(!board.isWalkable(obsX, obsY));
    board.setTile(obsX, obsY, '#');
}

void Game::update(Direction dir) {
    processMovement(dir);
    addRandomObstacle();
}

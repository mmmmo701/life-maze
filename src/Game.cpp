#include "Game.h"
#include <cstdlib>
#include <iostream>

Game::Game() : player(board.getBOARD_SIZE() / 2, board.getBOARD_SIZE() / 2), board() {}

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
    #ifdef DEBUG
    std::cout << "DEBUG: Attempting to move player to (" << newPlayerX << ", " << newPlayerY << ")" << std::endl;
    #endif
    if(board.isValidTile(newPlayerX, newPlayerY) && board.isWalkable(newPlayerX, newPlayerY)) {
        player.move(DIRDX[dirInt], DIRDY[dirInt]);
    }
}

void Game::addRandomObstacle() {
    int obsX = 0, obsY = 0;
    do {
        obsX = rand() % board.getBOARD_SIZE();
        obsY = rand() % board.getBOARD_SIZE();
    } while(!board.isWalkable(obsX, obsY));
    board.setTile(obsX, obsY, '#');
}

void Game::update(Direction dir) {
    #ifdef DEBUG
    std::cout << "DEBUG: Updating game state with direction " << static_cast<int>(dir) << std::endl;
    #endif
    processMovement(dir);
    addRandomObstacle();
}

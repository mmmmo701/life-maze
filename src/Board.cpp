#include "Board.h"
#include "contract.h"
#include <cassert>
#include <cstdlib>

Board::Board() {
    int i,j;
    std::vector<char> dummy;
    for(i=0; i<BOARD_SIZE; i++) {
        grid.push_back(dummy);
        for(j=0; j<BOARD_SIZE; j++){
            if(i==0 || i==BOARD_SIZE-1 || j==0 || j==BOARD_SIZE-1 || 
                (rand()%5==0 && (i%2==0) && (j%2==0) && i!=BOARD_SIZE/2 && j!=BOARD_SIZE/2))
                grid[i].push_back('#'); // Wall
            else
                grid[i].push_back('.');
        }
    }
}

bool Board::isValidTile(int x, int y) {
    return x>=0 && x<BOARD_SIZE && y>=0 && y<BOARD_SIZE;
}

char Board::getTile(int x, int y) {
    REQUIRES(isValidTile(x, y));
    return grid[x][y];
}

void Board::setTile(int x, int y, char c) {
    REQUIRES(isValidTile(x, y));
    grid[x][y] = c;
}

bool Board::isWalkable(int x, int y) {
    REQUIRES(isValidTile(x, y));
    return getTile(x, y) == '.';
}

int Board::getBOARD_SIZE() const {
    return BOARD_SIZE;
}

#include "board.h"
#include <cassert>

Board::board() {
    int i,j;
    for(i=0; i<BOARD_SIZE; i++)
        for(j=0; j<BOARD_SIZE; j++)
            grid[i][j] = '.';
}

bool Board::isValidTile(int x, int y) {
    return x>=0 && x<BOARD_SIZE && y>=0 && y<BOARD_SIZE;
}

char Board::getTile(int x, int y) const {
    assert(isValidTile(x, y));
    return grid[x][y];
}

char Board::setTile(int x, int y, char c) {
    assert(isValidTile(x, y));
    grid[x][y] = c;
}

bool Board::isWalkable(int x, int y) const {
    assert(isValidTile(x, y));
    return getTile(x, y) == '.';
}

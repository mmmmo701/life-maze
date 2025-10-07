#include "Board.h"
#include <cassert>
#include <cstdlib>

Board::Board() {
    int i,j;
    std::vector<char> dummy;
    for(i=0; i<BOARD_SIZE; i++) {
        grid.push_back(dummy);
        for(j=0; j<BOARD_SIZE; j++)
            grid[i].push_back('.');
    }
}

bool Board::isValidTile(int x, int y) {
    return x>=0 && x<BOARD_SIZE && y>=0 && y<BOARD_SIZE;
}

char Board::getTile(int x, int y) {
    assert(isValidTile(x, y));
    return grid[x][y];
}

void Board::setTile(int x, int y, char c) {
    assert(isValidTile(x, y));
    grid[x][y] = c;
}

bool Board::isWalkable(int x, int y) {
    assert(isValidTile(x, y));
    return getTile(x, y) == '.';
}

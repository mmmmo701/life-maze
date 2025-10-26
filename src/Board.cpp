#include "Board.h"
#include "contract.h"
#include <cassert>
#include <cstdlib>

Board::Board() {
    int i,j;
    std::vector<char> gridDummy(BOARD_SIZE);
    std::vector<Color> colorDummy(BOARD_SIZE);
    for(i=0; i<BOARD_SIZE; i++) {
        grid.push_back(gridDummy);
        color.push_back(colorDummy);
        for(j=0; j<BOARD_SIZE; j++){
            if(i==0 || i==BOARD_SIZE-1 || j==0 || j==BOARD_SIZE-1 || 
                (rand()%5==0 && (i%2==0) && (j%2==0) && i!=BOARD_SIZE/2 && j!=BOARD_SIZE/2))
                grid[i][j] = '#'; // Wall
            else
                grid[i][j] = EMPTY;
            color[i][j] = Color::DEFAULT;
        }
    }
}

bool Board::isValidTile(std::pair<int,int> pos) {
    int x = pos.first, y = pos.second;
    return x>=0 && x<BOARD_SIZE && y>=0 && y<BOARD_SIZE;
}

char Board::getTile(std::pair<int,int> pos) {
    REQUIRES(isValidTile(pos));
    return grid[pos.first][pos.second];
}

Color Board::getColor(std::pair<int,int> pos) {
    REQUIRES(isValidTile(pos));
    return color[pos.first][pos.second];
}

void Board::setTile(std::pair<int,int> pos, char c, Color color) {
    REQUIRES(isValidTile(pos));
    grid[pos.first][pos.second] = c;
    this->color[pos.first][pos.second] = color;
}

bool Board::isWalkable(std::pair<int,int> pos) {
    REQUIRES(isValidTile(pos));
    return getTile(pos) == EMPTY;
}

int Board::getBOARD_SIZE() const {
    return BOARD_SIZE;
}

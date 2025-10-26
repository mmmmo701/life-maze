#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <utility>

const char EMPTY = ' ';

enum class Color { DEFAULT, BLUE, YELLOW, RED, MAGNENTA };

class Board {
public:
    Board(); // Constructor can set up the initial maze.

    // Position-based APIs use std::pair<int,int>
    char getTile(std::pair<int,int> pos);
    Color getColor(std::pair<int,int> pos);
    void setTile(std::pair<int,int> pos, char c, Color color);

    // Checks if a given coordinate is a valid, walkable space.
    bool isWalkable(std::pair<int,int> pos);
    bool isValidTile(std::pair<int,int> pos);
    int getSize() const;
    int getBOARD_SIZE() const;

private:
    // A 2D vector is more flexible than a C-style array.
    std::vector<std::vector<char> > grid;
    std::vector<std::vector<Color> > color;
    static const int BOARD_SIZE = 200;
};

#endif //BOARD_H

#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
public:
    Board(); // Constructor can set up the initial maze.

    char getTile(int x, int y) const;
    void setTile(int x, int y, char c);

    // Checks if a given coordinate is a valid, walkable space.
    bool isWalkable(int x, int y) const;
    int getSize() const;

private:
    bool isValidTile(int x, int y);
    // A 2D vector is more flexible than a C-style array.
    std::vector<std::vector<char>> grid;
    static const int BOARD_SIZE = 200;
};

#endif //BOARD_H

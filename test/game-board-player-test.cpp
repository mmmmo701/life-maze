#include "Game.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

void assertPlayerAttr(Player p, int x, int y, int hp) const {
    assert(p.getX() == x);
    assert(p.getY() == y);
    assert(p.getHP() == hp);
}

int main(){
    Player testPlayer = Player(3,5);
    testPlayer.move(1,0);
    assertPlayerAttr(testPlayer,4,5,1000);
    testPlayer.takeDamage(350);
    assertPlayerAttr(testPlayer,4,5,650);
    testPlayer.move(0,-3);
    testPlayer.takeDamage(650);
    assertPlayerAttr(testPlayer,4,2,0);
    assert(!testPlayer.isAlive());

    Board board = board();
    assert(board.isValidTile(150, 150));
    assert(board.isValidTile(100, 0));
    assert(board.isValidTile(0, 199));
    assert(!board.isValidTile(150, 200));
    assert(!board.isValidTile(-1, 0));
    board.setTile(10,30,'#');
    assert(isPositionValid(10,31));
    assert(!isPositionValid(10,30));

    Game game = game();
    assert(game.player.getX() == game.board.BOARD_SIZE()/2);
    assert(game.player.getY() == game.board.BOARD_SIZE()/2);
    game.update(Direction.UP);
    assert(game.player.getX() == game.board.BOARD_SIZE()/2 - 1);
    bool flag = false;
    for(int i=0; i<game.board.BOARD_SIZE(); i++)
        for(int j=0; j<game.board.BOARD_SIZE(); j++)
            flag = flag || (!game.board.isWalkable(i,j));
    assert(flag);

    std::cout << "All test passed!\n";
    return 0;
}

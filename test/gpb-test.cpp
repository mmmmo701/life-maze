#include "test.h"

void assertPlayerAttr(Player p, int x, int y, int hp) {
    assert(p.getX() == x);
    assert(p.getY() == y);
    assert(p.getHP() == hp);
}

void testingPlayer() {
    Player testPlayer = Player(3,5);
    testPlayer.move(1,0);
    assertPlayerAttr(testPlayer,4,5,1000);
    testPlayer.takeDamage(350);
    assertPlayerAttr(testPlayer,4,5,650);
    testPlayer.move(0,-3);
    testPlayer.takeDamage(650);
    assertPlayerAttr(testPlayer,4,2,0);
    assert(!testPlayer.isAlive());
}

void testingBoard() {
    Board board = Board();
    assert(board.isValidTile(150, 150));
    assert(board.isValidTile(100, 0));
    assert(board.isValidTile(0, 199));
    assert(!board.isValidTile(150, 200));
    assert(!board.isValidTile(-1, 0));
    board.setTile(10,30,'#');
    assert(board.isWalkable(10,31));
    assert(!board.isWalkable(10,30));
}

void testingGame() {
    Game game = Game();
    assert(game.getPlayer().getX() == game.getBoard().BOARD_SIZE/2);
    assert(game.getPlayer().getY() == game.getBoard().BOARD_SIZE/2);
    game.update(Direction::UP);
    assert(game.getPlayer().getX() == game.getBoard().BOARD_SIZE/2 - 1);
    bool flag = false;
    for(int i=0; i<game.getBoard().BOARD_SIZE; i++)
        for(int j=0; j<game.getBoard().BOARD_SIZE; j++)
            flag = flag || (!game.getBoard().isWalkable(i,j));
    assert(flag);
}



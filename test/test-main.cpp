#include <iostream>
#include "test.h"

void basicTest(){
    testingPlayer();
    testingBoard();
    testingGame();
    std::cout << "All test passed!\n";
}

int main() {
    rendererTest();
    return 0;
}
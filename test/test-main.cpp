#include <iostream>
#include "test.h"

void basicTest(){
    testingPlayer();
    testingBoard();
    testingGame();
    std::cout << "All test passed!\n";
    return 0;
}

int main() {
    rendererTest();
    return 0;
}
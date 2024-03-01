#include <iostream>
#include "GameBoard.h"
#include "Move.h"

using namespace std;

int main() {
    // GameBoard game;
    // game.printBoard();

    VecBoard board;
    board.move(7, 7, 3, 3);
    board.printBoard();

    return 0;
}
#include <iostream>
#include "GameBoard.h"
#include "PGNReader.h"

using namespace std;

int main() {
    PGNReader reader("games.pgn");
    PGNReader::Game game = reader.parseGame();
    GameBoard board = reader.createBoard(game);
    board.print();

    return 0;
}
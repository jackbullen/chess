#include <iostream>

#include "GameBoard.h"
#include "PGNReader.h"

using namespace std;

int main() {
    PGNReader reader("games.pgn");
    PGNReader::Game game = reader.parseGame();
    GameBoard board = reader.printGame(game);
    game = reader.parseGame();
    board = reader.printGame(game);
    // board.print();
    return 0;
}
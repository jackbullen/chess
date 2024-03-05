#include <iostream>

#include "GameBoard.h"
#include "PGNReader.h"

using namespace std;

int main() {
    PGNReader reader("games.pgn");
    while (1) {
        PGNReader::Game game = reader.parseGame();
        if (game.moves.size() == 0) {
            break;
        }
        GameBoard board = reader.printGame(game);
    }
    return 0;
}
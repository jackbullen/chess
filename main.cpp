#include <iostream>

#include "GameBoard.h"
#include "PGNReader.h"

using namespace std;

int main() {
    // Create a PGNReader object
    PGNReader reader("games.pgn");

    // Parse the first game in games.pgn
    GameBoard board = reader.parseGame();

    // Loop over all games in a file    
    // while (1) {
    //     PGNReader::Game game = reader.parseGame();
    //     if (game.moves.size() == 0) {
    //         break;
    //     }
    //     GameBoard board = reader.printGame(game);
    // }

    return 0;
}
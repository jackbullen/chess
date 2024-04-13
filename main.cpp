#include <iostream>

#include "GameBoard.h"
#include "PGNReader.h"

using namespace std;

int main() {
    PGNReader reader("games.pgn");

    // Parse the first game in games.pgn
    PGNReader::Game game = reader.parseGame();

    // Print the game
    GameBoard board = reader.printGame(game);

    // Print the board object
    // board.print();

    // Todo
    // board.prev();
    // board.next();
    // board.eval();
    // board.play();

    // Loop over all games in a file    
    // while (1) {
        // PGNReader::Game game = reader.parseGame();
        // if (game.moves.size() == 0) {
            // break;
        // }
        // GameBoard board = reader.printGame(game);
    // }


    return 0;
}
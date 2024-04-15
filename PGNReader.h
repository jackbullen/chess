// PGNReader.h
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "GameBoard.h"
#include "VecBoard.h"

using namespace std;

class PGNReader {
   public:
    struct Game {
        string event;
        string site;
        string date;
        string round;
        string white;
        string black;
        string result;
        string whiteElo;
        string blackElo;
        string eco;
        vector<string> moves;
    };

    PGNReader(const string& filename);
    GameBoard parseGame();
    GameBoard printGame(const Game& game);

   private:
    ifstream file;
};

// PGNReader.h
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "VecBoard.h"
#include "GameBoard.h"

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
    Game parseGame();
    GameBoard createBoard(const Game& game);

private:
    ifstream file;
};
#include "VecBoard.h"

using namespace std;

struct BoardState {
    VecBoard board;
    vector< vector<bool> > pawnMoves;
    vector< vector<bool> > castleWhite;
    vector< vector<bool> > castleBlack;
};
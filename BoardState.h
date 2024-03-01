#include "VecBoard.h"

struct BoardState {
    VecBoard board;
    std::vector< std::vector<bool> > pawnMoves;
    std::vector< std::vector<bool> > castleWhite;
    std::vector< std::vector<bool> > castleBlack;
};
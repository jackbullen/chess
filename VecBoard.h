#include <vector>
#include "Piece.h"

class VecBoard {
public:
    static constexpr int BOARD_SIZE = 8;
    VecBoard();
    std::vector< std::vector<Piece> > board;
    bool isWhiteTurn;
    Piece getPiece(int x, int y) const {
        return board[x][y];
    }
    void printBoard();
};
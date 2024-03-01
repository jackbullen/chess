#include <vector>
#include "Piece.h"

using namespace std;

class VecBoard {
public:
    VecBoard();
    vector< std::vector<Piece> > board;
    int turn;

    // Constants
    static constexpr int BOARD_SIZE = 8;

    // VecBoard operations
    void forceMove(int fromX, int fromY, int toX, int toY);
    void move(int fromX, int fromY, int toX, int toY);
    // void move(string sanMove);
    // void move(Move move);
    // void move(vector<Move> moves);
    // void move(vector<string> sanMoves);

    // VecBoard utils
    void printBoard();

    Piece getPiece(int x, int y) const {
        return board[x][y];
    }

};
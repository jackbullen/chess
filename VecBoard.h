#ifndef VECBOARD_H
#define VECBOARD_H

#include <vector>

#include "Piece.h"

using namespace std;

class VecBoard {
   public:
    VecBoard();
    vector<vector<Piece>> board;
    int turn;
    static const int BOARD_SIZE;

    // VecBoard operations
    void start();
    void forceMove(int fromX, int fromY, int toX, int toY);
    void move(int fromX, int fromY, int toX, int toY);

    // VecBoard moves
    bool checkMove(int fromX, int fromY, int toX, int toY);
    bool isMoveInBounds(int x, int y);
    vector<pair<int, int>> getValidMoves(int x, int y);
    bool isBlocked(int fromX, int fromY, int toX, int toY);
    pair<pair<int, int>, pair<int, int>> sanToIndices(const string& san);
    
    void print();

    Piece getPiece(int x, int y) const {
        return board[x][y];
    }
};

#endif
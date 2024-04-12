#ifndef VECBOARD_H
#define VECBOARD_H

#include "Piece.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;

const int verbose = 0;

class VecBoard {
   public:
    VecBoard();
    vector<vector<Piece>> board;
    int turn;
    static const int BOARD_SIZE;
    map<char, PieceType> charPieceTypeMap = {
            {'R', ROOK},
            {'N', KNIGHT},
            {'B', BISHOP},
            {'Q', QUEEN}};

    // Modifies VecBoard
    void start();
    void forceMove(int fromX, int fromY, int toX, int toY);

    void move(string sanMove);
    vector<pair<int, int>> getValidMoves(int x, int y);
    pair<pair<int, int>, pair<int, int>> sanToIndices(const string& san);

    pair<int, int> diffToKing(int x, int y);
    bool checkMove(int fromX, int fromY, int toX, int toY);
    bool isMoveInBounds(int x, int y);
    bool isBlocked(int fromX, int fromY, int toX, int toY);    

    void print();

    Piece getPiece(int x, int y) const {
        return board[x][y];
    }
};

#endif
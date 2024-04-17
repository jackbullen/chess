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
            {'P', PAWN}, {'p', PAWN},
            {'R', ROOK}, {'r', ROOK},
            {'N', KNIGHT}, {'n', KNIGHT},
            {'B', BISHOP}, {'b', BISHOP},
            {'Q', QUEEN}, {'q', QUEEN},
            {'K', KING}, {'k', KING}};
    map<PieceType, int> pieceTypeValueMap = {
            {ROOK, 5}, {PAWN, 1},
            {BISHOP, 3}, {KNIGHT, 3},
            {QUEEN, 9}, {KING, 100}};
    // Modifies VecBoard
    void start();
    void load(string fen);
    void prev();
    void next();
    void forceMove(int fromX, int fromY, int toX, int toY);
    
    void move(string sanMove);
    vector<pair<int, int>> getValidMoves(int x, int y);
    pair<pair<int, int>, pair<int, int>> sanToIndices(const string& san);


    bool checkMove(int fromX, int fromY, int toX, int toY);
    bool isMoveInBounds(int x, int y);
    bool isBlocked(int fromX, int fromY, int toX, int toY);    
    pair<int, int> checkPin(int x, int y);
    pair<int, int> diffToKing(int x, int y);

    void print();

    Piece getPiece(int x, int y) const {
        return board[x][y];
    }

    int eval();
};

#endif
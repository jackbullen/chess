#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <map>
#include "VecBoard.h"

using namespace std;

class GameBoard {
   public:
    GameBoard();
    void reset();
    void load(string fen);
    void move(string san);
    void print();
    Piece getPiece(int x, int y);
    vector<pair<int, int>> getValidMoves(int x, int y);
    string loc(int x, int y);
    map<PieceType, string> pieceTypeNameMap = {
    {PAWN, "Pawn"},
    {ROOK, "Rook"},
    {KNIGHT, "Knight"},
    {BISHOP, "Bishop"},
    {QUEEN, "Queen"},
    {KING, "King"}};
    
   private:
    VecBoard vecBoard;
};

#endif
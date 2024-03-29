#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <map>

#include "VecBoard.h"

using namespace std;

class GameBoard {
   public:
    GameBoard();
    void reset();
    void move(string san);
    void print();
    Piece getPiece(int x, int y);
    string loc(int x, int y);
    map<PieceType, string> pieceTypeNameMap;
    map<char, PieceType> charPieceTypeMap;
    map<char, int> fileMap;

   private:
    VecBoard vecBoard;
};

#endif
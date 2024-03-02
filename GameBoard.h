#include <map>

#include "VecBoard.h"

using namespace std;

class GameBoard {
   public:
    GameBoard();
    void move(string san);
    void print();
    Piece getPiece(int x, int y);
    string loc(int x, int y);
    map<PieceType, string> pieceTypeNameMap;
    map<char, int> fileMap;

   private:
    VecBoard vecBoard;
};
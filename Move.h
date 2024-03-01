#include <vector>
#include "Piece.h"

bool checkMove(int fromX, int fromY, int toX, int toY);

class Move {
public:
    std::vector<std::pair<int, int>> getValidMoves(Piece piece, int x, int y);
    bool isValidPosition(int x, int y);
};
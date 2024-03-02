#include "GameBoard.h"

#include <iostream>

using namespace std;

GameBoard::GameBoard() {
    pieceTypeNameMap = {
        {PAWN, "Pawn"},
        {ROOK, "Rook"},
        {KNIGHT, "Knight"},
        {BISHOP, "Bishop"},
        {QUEEN, "Queen"},
        {KING, "King"}};

    fileMap = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7}};
}

void GameBoard::move(string sanMove) {
    pair<pair<int, int>, pair<int, int>> indices = vecBoard.sanToIndices(sanMove);
    pair<int, int> from = indices.first;
    pair<int, int> to = indices.second;
    vecBoard.move(from.first, from.second, to.first, to.second);
}

void GameBoard::print() {
    vecBoard.print();
}

Piece GameBoard::getPiece(int x, int y) {
    return vecBoard.getPiece(x, y);
}

string GameBoard::loc(int x, int y) {
    return pieceTypeNameMap[vecBoard.getPiece(x, y).type];
}
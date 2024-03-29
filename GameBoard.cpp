#include "GameBoard.h"

#include <iostream>

using namespace std;

const int verbose = 0;

GameBoard::GameBoard() {
    pieceTypeNameMap = {
        {PAWN, "Pawn"},
        {ROOK, "Rook"},
        {KNIGHT, "Knight"},
        {BISHOP, "Bishop"},
        {QUEEN, "Queen"},
        {KING, "King"}};
    charPieceTypeMap = {
        {'R', ROOK},
        {'N', KNIGHT},
        {'B', BISHOP},
        {'Q', QUEEN}};
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
    if (verbose) {
        cout << "Indices: (" << indices.first.first << " " << indices.first.second << ") -> (" << indices.second.first << " " << indices.second.second << ")" << endl;
    }
    pair<int, int> from = indices.first;
    pair<int, int> to = indices.second;
    if (sanMove[sanMove.size() - 2] == '=') {// Promotion
        vecBoard.move(from.first, from.second, to.first, to.second, charPieceTypeMap[sanMove[sanMove.size() - 1]]);
    } else if (sanMove[sanMove.size() - 3] == '=') {// Promotion with check
        vecBoard.move(from.first, from.second, to.first, to.second, charPieceTypeMap[sanMove[sanMove.size() - 2]]);
    } else {// Other moves
        vecBoard.move(from.first, from.second, to.first, to.second);
    }
}

void GameBoard::reset() {
    vecBoard.start();
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
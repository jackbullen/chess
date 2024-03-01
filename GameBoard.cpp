#include "GameBoard.h"

#include <iostream>

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

void GameBoard::move(std::string sanMove) {
    // TODO: Implement SAN parsing and move logic
}

void GameBoard::printBoard() {
    vecBoard.printBoard();
}

Piece GameBoard::getPiece(int x, int y) {
    return vecBoard.getPiece(x, y);
}

string GameBoard::loc(int x, int y) {
    return pieceTypeNameMap[vecBoard.getPiece(x, y).type];
}
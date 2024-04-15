#include "GameBoard.h"

#include <iostream>

using namespace std;

GameBoard::GameBoard() {}

void GameBoard::move(string sanMove) {
    vecBoard.move(sanMove);
}

void GameBoard::reset() {
    vecBoard.start();
}

void GameBoard::load(string fen) {
    vecBoard.load(fen);
}

void GameBoard::print() {
    vecBoard.print();
}

Piece GameBoard::getPiece(int x, int y) {
    return vecBoard.getPiece(x, y);
}

vector<pair<int, int>> GameBoard::getValidMoves(int x, int y) {
    return vecBoard.getValidMoves(x, y);
}

string GameBoard::loc(int x, int y) {
    return pieceTypeNameMap[vecBoard.getPiece(x, y).type];
}
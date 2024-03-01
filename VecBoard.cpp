#include "VecBoard.h"
#include "Move.h"
#include <iostream>

using namespace std;

VecBoard::VecBoard(): turn(1) {
    board.resize(BOARD_SIZE, vector<Piece>(BOARD_SIZE, Piece(EMPTY, 0, 0)));

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = Piece(PAWN, 1, 1);
        board[6][i] = Piece(PAWN, 0, 1);
    }

    board[0][0] = Piece(ROOK, -1, 5);
    board[0][7] = Piece(ROOK, -1, 5);
    board[7][0] = Piece(ROOK, 1, 5);
    board[7][7] = Piece(ROOK, 1, 5);

    board[0][1] = Piece(KNIGHT, -1, 3);
    board[0][6] = Piece(KNIGHT, -1, 3);
    board[7][1] = Piece(KNIGHT, 1, 3);
    board[7][6] = Piece(KNIGHT, 1, 3);

    board[0][2] = Piece(BISHOP, -1, 3);
    board[0][5] = Piece(BISHOP, -1, 3);
    board[7][2] = Piece(BISHOP, 1, 3);
    board[7][5] = Piece(BISHOP, 1, 3);

    board[0][3] = Piece(QUEEN, -1, 9);
    board[7][3] = Piece(QUEEN, 1, 9);

    board[0][4] = Piece(KING, -1, 100);
    board[7][4] = Piece(KING, 1, 100);
}

void VecBoard::forceMove(int fromX, int fromY, int toX, int toY) {
    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = Piece(EMPTY, 0, 0);
}

void VecBoard::move(int fromX, int fromY, int toX, int toY) {
    if (board[fromX][fromY].type == EMPTY) {
        throw invalid_argument("MoveError: Attempting to move from an empty square\n");
        return;
    }
    if (board[fromX][fromY].color != turn) {
        throw invalid_argument("MoveError: Attempting to move the wrong color piece\n");
        return;
    }
    if (board[toX][toY].color == turn) {
        throw invalid_argument("MoveError: Attempting to capture your own piece\n");
        return;
    }
    if (!checkMove(fromX, fromY, toX, toY)) {
        throw invalid_argument("MoveError: Invalid move\n");
        return;
    }
    forceMove(fromX, fromY, toX, toY);
    turn = !turn;
}

void VecBoard::printBoard() {
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            string symbol;
            switch (board[i][j].type) {
                case EMPTY:
                    symbol = ".";
                    break;
                case PAWN:
                    if (board[i][j].color == -1)
                        symbol = 'p';
                    else
                        symbol = 'P';
                    break;
                case ROOK:
                    if (board[i][j].color == -1)
                        symbol = 'r';
                    else
                        symbol = 'R';
                    break;
                case KNIGHT:
                    if (board[i][j].color == -1)
                        symbol = 'n';
                    else
                        symbol = 'N';
                    break;
                case BISHOP:
                    if (board[i][j].color == -1)
                        symbol = 'b';
                    else
                        symbol = 'B';
                    break;
                case QUEEN:
                    if (board[i][j].color == -1)
                        symbol = 'q';
                    else
                        symbol = 'Q';
                    break;
                case KING:
                    if (board[i][j].color == 1)
                        symbol = 'k';
                    else
                        symbol = 'K';
                    break;
            }
            cout << symbol << ' ';
        }
        cout << endl;
    }
    cout << endl;
}
#include "VecBoard.h"
#include <iostream>

using namespace std;

VecBoard::VecBoard() {
        board.resize(BOARD_SIZE, vector<Piece>(BOARD_SIZE, Piece(EMPTY, 0, 0)));

        for (int i = 0; i < BOARD_SIZE; i++) {
            board[1][i] = Piece(PAWN, 1, 1);
            board[6][i] = Piece(PAWN, 0, 1);
        }

        board[0][0] = Piece(ROOK, 1, 5);
        board[0][7] = Piece(ROOK, 1, 5);
        board[7][0] = Piece(ROOK, 0, 5);
        board[7][7] = Piece(ROOK, 0, 5);

        board[0][1] = Piece(KNIGHT, 1, 3);
        board[0][6] = Piece(KNIGHT, 1, 3);
        board[7][1] = Piece(KNIGHT, 0, 3);
        board[7][6] = Piece(KNIGHT, 0, 3);

        board[0][2] = Piece(BISHOP, 1, 3);
        board[0][5] = Piece(BISHOP, 1, 3);
        board[7][2] = Piece(BISHOP, 0, 3);
        board[7][5] = Piece(BISHOP, 0, 3);

        board[0][3] = Piece(QUEEN, 1, 9);
        board[7][3] = Piece(QUEEN, 0, 9);
        
        board[0][4] = Piece(KING, 1, 100);
        board[7][4] = Piece(KING, 0, 100);
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
                    if (board[i][j].isWhite)
                        symbol = 'p';
                    else
                        symbol = 'P';
                    break;
                case ROOK:
                    if (board[i][j].isWhite)
                        symbol = 'r';
                    else
                        symbol = 'R';
                    break;
                case KNIGHT:
                    if (board[i][j].isWhite)
                        symbol = 'n';
                    else
                        symbol = 'N';
                    break;
                case BISHOP:
                    if (board[i][j].isWhite)
                        symbol = 'b';
                    else
                        symbol = 'B';
                    break;
                case QUEEN:
                    if (board[i][j].isWhite)
                        symbol = 'q';
                    else
                        symbol = 'Q';
                    break;
                case KING:
                    if (board[i][j].isWhite)
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
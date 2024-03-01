#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8;

enum PieceType {
    EMPTY,
    KING,
    KNIGHT,
    QUEEN,
    PAWN,
    ROOK,
    BISHOP
};

struct Piece {
    PieceType type;
    bool isFirst;

    Piece(PieceType type, bool isFirst) : type(type), isFirst(isFirst) {}
};

class Board {
private:
    vector< vector<Piece> > board;

public:
    Board() {
        board.resize(BOARD_SIZE, vector<Piece>(BOARD_SIZE, Piece(QUEEN, false)));
    }

    void printBoard() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                char symbol = ' ';
                switch (board[i][j].type) {
                    case EMPTY:
                        symbol = ' ';
                        break;
                    case PAWN:
                        symbol = 'P';
                        break;
                    case ROOK:
                        symbol = 'R';
                        break;
                    case KNIGHT:
                        symbol = 'N';
                        break;
                    case BISHOP:
                        symbol = 'B';
                        break;
                    case QUEEN:
                        symbol = 'Q';
                        break;
                    case KING:
                        symbol = 'K';
                        break;
                }
                cout << symbol << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    Board board;
    board.printBoard();
    return 0;
}
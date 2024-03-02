#include "VecBoard.h"

#include <iostream>
#include <map>

using namespace std;

const int VecBoard::BOARD_SIZE = 8;

VecBoard::VecBoard() : turn(1) {
    start();
}

void VecBoard::start() {
    // Sets the board to the starting position
    board.resize(BOARD_SIZE, vector<Piece>(BOARD_SIZE, Piece(EMPTY, 0, 0)));
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = Piece(PAWN, -1, 1);
        board[6][i] = Piece(PAWN, 1, 1);
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
    turn = 1;
}

void VecBoard::forceMove(int fromX, int fromY, int toX, int toY) {
    // Moves a piece from (fromX, fromY) to (toX, toY)
    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = Piece(EMPTY, 0, 0);
}

void VecBoard::move(int fromX, int fromY, int toX, int toY) {
    // Handles moving of pieces by checking for validity and calling forceMove
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
        // TODO: Better exception handling for checkMove returning false.
        //       Could throw better exception inside checkMove
        throw invalid_argument("MoveError: Invalid move\n");
        return;
    }
    forceMove(fromX, fromY, toX, toY);
    if (turn == 1) {
        turn = -1;
    } else {
        turn = 1;
    }
}

bool VecBoard::checkMove(int fromX, int fromY, int toX, int toY) {
    // Returns true if the move is valid, false otherwise
    vector<pair<int, int>> validMoves = getValidMoves(fromX, fromY);
    for (auto move : validMoves) {
        if (move.first == toX && move.second == toY) {
            return true;
        }
    }
    return false;
}

bool VecBoard::isBlocked(int fromX, int fromY, int toX, int toY) {
    // Returns true if there is a piece obstructing the move from (fromX, fromY) to (toX, toY)
    int dx = toX - fromX;
    int dy = toY - fromY;
    if (dx == 0 && dy == 0) {
        return false;
    }
    if (dx == 0) {
        for (int i = 1; i < abs(dy); i++) {
            if (dy > 0) {
                if (board[fromX][fromY + i].type != EMPTY) {
                    return true;
                }
            } else {
                if (board[fromX][fromY - i].type != EMPTY) {
                    return true;
                }
            }
        }
    } else if (dy == 0) {
        for (int i = 1; i < abs(dx); i++) {
            if (dx > 0) {
                if (board[fromX + i][fromY].type != EMPTY) {
                    return true;
                }
            } else {
                if (board[fromX - i][fromY].type != EMPTY) {
                    return true;
                }
            }
        }
    } else if (abs(dx) == abs(dy)) {
        for (int i = 1; i < abs(dx); i++) {
            if (dx > 0 && dy > 0) {
                if (board[fromX + i][fromY + i].type != EMPTY) {
                    return true;
                }
            } else if (dx > 0 && dy < 0) {
                if (board[fromX + i][fromY - i].type != EMPTY) {
                    return true;
                }
            } else if (dx < 0 && dy > 0) {
                if (board[fromX - i][fromY + i].type != EMPTY) {
                    return true;
                }
            } else {
                if (board[fromX - i][fromY - i].type != EMPTY) {
                    return true;
                }
            }
        }
    }
    return false;
}

vector<pair<int, int>> VecBoard::getValidMoves(int x, int y) {
    // Returns a vector of valid moves for a piece at position (x, y)
    Piece piece = board[x][y];
    vector<pair<int, int>> moves;
    int dxKnight[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dyKnight[] = {1, 2, 2, 1, -1, -2, -2, -1};
    switch (piece.type) {
        case EMPTY:
            break;
        case KING:
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (isMoveInBounds(x + i, y + j)) {
                        moves.push_back({x + i, y + j});
                    }
                }
            }
            // Handle castling
            if (piece.color == 1) {
                if (x == 7 && y == 4) {
                    if (board[7][7].type == ROOK && board[7][7].color == 1) {
                        if (board[7][5].type == EMPTY && board[7][6].type == EMPTY) {
                            moves.push_back({7, 6});
                        }
                    }
                    if (board[7][0].type == ROOK && board[7][0].color == 1) {
                        if (board[7][1].type == EMPTY && board[7][2].type == EMPTY && board[7][3].type == EMPTY) {
                            moves.push_back({7, 2});
                        }
                    }
                }
            } else {
                if (x == 0 && y == 4) {
                    if (board[0][7].type == ROOK && board[0][7].color == -1) {
                        if (board[0][5].type == EMPTY && board[0][6].type == EMPTY) {
                            moves.push_back({0, 6});
                        }
                    }
                    if (board[0][0].type == ROOK && board[0][0].color == -1) {
                        if (board[0][1].type == EMPTY && board[0][2].type == EMPTY && board[0][3].type == EMPTY) {
                            moves.push_back({0, 2});
                        }
                    }
                }
            }

            break;
        case KNIGHT:
            for (int i = 0; i < 8; i++) {
                int newX = x + dxKnight[i];
                int newY = y + dyKnight[i];
                if (isMoveInBounds(newX, newY)) {
                    moves.push_back({newX, newY});
                }
            }
            break;
        case ROOK:
            // Check in all four directions until you hit the edge of the board or another piece
            for (int dx = -1; dx <= 1; dx += 2) {
                for (int dy = -1; dy <= 1; dy += 2) {
                    int newX = x + dx;
                    int newY = y + dy;
                    while (isMoveInBounds(newX, newY)) {
                        moves.push_back({newX, newY});
                        newX += dx;
                        newY += dy;
                    }
                }
            }
            break;
        case BISHOP:
            // Handle bishop move logic
            // Add debug printing
            for (int dx = -1; dx <= 1; dx += 2) {
                for (int dy = -1; dy <= 1; dy += 2) {
                    int newX = x + dx;
                    int newY = y + dy;

                    while (isMoveInBounds(newX, newY) && board[newX][newY].color != piece.color) {
                        moves.push_back({newX, newY});
                        newX += dx;
                        newY += dy;
                    }
                }
            }

            break;
        case QUEEN:
            // Check in all eight directions until you hit the edge of the board or another piece
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }
                    int newX = x + dx;
                    int newY = y + dy;
                    while (isMoveInBounds(newX, newY) && board[newX][newY].color != piece.color) {
                        moves.push_back({newX, newY});
                        newX += dx;
                        newY += dy;
                    }
                }
            }
            break;
        case PAWN:
            if (piece.color == 1) {
                if (isMoveInBounds(x - 1, y) && board[x - 1][y].type == EMPTY) {
                    moves.push_back({x - 1, y});
                }
                if (x == 6 && board[x - 1][y].type == EMPTY && board[x - 2][y].type == EMPTY) {
                    moves.push_back({x - 2, y});
                }
                if (isMoveInBounds(x - 1, y - 1) && board[x - 1][y - 1].color == -1) {
                    moves.push_back({x - 1, y - 1});
                }
                if (isMoveInBounds(x - 1, y + 1) && board[x - 1][y + 1].color == -1) {
                    moves.push_back({x - 1, y + 1});
                }
            } else {
                if (isMoveInBounds(x + 1, y) && board[x + 1][y].type == EMPTY) {
                    moves.push_back({x + 1, y});
                }
                if (x == 1 && board[x + 1][y].type == EMPTY && board[x + 2][y].type == EMPTY) {
                    moves.push_back({x + 2, y});
                }
                if (isMoveInBounds(x + 1, y - 1) && board[x + 1][y - 1].color == 1) {
                    moves.push_back({x + 1, y - 1});
                }
                if (isMoveInBounds(x + 1, y + 1) && board[x + 1][y + 1].color == 1) {
                    moves.push_back({x + 1, y + 1});
                }
            }
            break;
    }
    return moves;
}

bool VecBoard::isMoveInBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

void VecBoard::print() {
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
                    if (board[i][j].color == -1)
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

pair<pair<int, int>, pair<int, int>> VecBoard::sanToIndices(const string& san) {
    map<char, int> file_to_col = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
    char piece = san[0];
    int destRow = 8 - (san[san.length() - 1] - '0');
    int destCol = file_to_col[san[san.length() - 2]];
    // cout << "Piece: " << piece << endl;
    // cout << "destRow: " << destRow << endl;
    // cout << "destCol: " << destCol << endl;

    map<char, PieceType> charToPieceType = {{'r', ROOK}, {'n', KNIGHT}, {'b', BISHOP}, {'q', QUEEN}, {'k', KING},
                                        {'R', ROOK}, {'N', KNIGHT}, {'B', BISHOP}, {'Q', QUEEN}, {'K', KING}};

    if (san == "O-O") {
        if (turn == 1) {
            return make_pair(make_pair(7, 4), make_pair(7, 6));
        } else {
            return make_pair(make_pair(0, 4), make_pair(0, 6));
        }
    } else if (san == "O-O-O") {
        if (turn == 1) {
            return make_pair(make_pair(7, 4), make_pair(7, 2));
        } else {
            return make_pair(make_pair(0, 4), make_pair(0, 2));
        }
    }

    // If san length is 2, then it's a pawn move: e5, d4, g3, ...
    if (san.length() == 2) {
        cout << endl << endl << "# 2 letter" <<  endl;
    } 
    
    // If san length is 3, then it's a piece move: Nf3, Bb5, ...
    else if (san.length() == 3) {
        cout << endl << endl << "# 3 letter" << endl;
    }

    // If san length is 4, then it's a capture: Nxf3, Bxb5 or ambiguous move: Nbd7, R1e2, or pawn promotion: e8=Q, or
    else if (san.length() == 4) {
        cout << endl << endl << "# 4 letter" << endl;
    }

    
    



    // for (int i = 0; i < 8; ++i) {
    //     for (int j = 0; j < 8; ++j) {
    //         if (VecBoard::getPiece(i, j) == piece) {
    //             vector<pair<int, int>> validMoves = VecBoard::getValidMoves(i, j);
    //             if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
    //                 return make_pair(make_pair(i, j), make_pair(destRow, destCol));
    //             }
    //         }
    //     }
    // }

    return make_pair(make_pair(-1, -1), make_pair(-1, -1));  // Return invalid pairs if no valid move is found
}
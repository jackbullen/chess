#include "VecBoard.h"

#include <iostream>
#include <map>

using namespace std;
const int verbose = 0;
const int VecBoard::BOARD_SIZE = 8;

VecBoard::VecBoard() : turn(1) {
    start();
}

void VecBoard::start() {
    // Sets the board to the starting position
    board.resize(BOARD_SIZE, vector<Piece>(BOARD_SIZE, Piece(EMPTY, 0, 0)));
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = Piece(EMPTY, 0, 0);
        }
    }
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

void VecBoard::move(int fromX, int fromY, int toX, int toY, PieceType promotionType) {
    // Reset enPassant flags
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j].enPassant = 0;
        }
    }
    // Handles moving of pieces by checking for validity and calling forceMove
    if (board[fromX][fromY].type == EMPTY) {
        throw invalid_argument("MoveError: move from an empty square\n");
        return;
    }
    if (board[fromX][fromY].color != turn) {
        throw invalid_argument("MoveError: move the wrong color piece\n");
        return;
    }
    if (board[toX][toY].color == turn) {
        throw invalid_argument("MoveError: capture your own piece\n");
        return;
    }
    // Promotion: Anytime a pawn moves to the last rank, it promotes to a queen
    if (board[fromX][fromY].type == PAWN && (toX == 0 || toX == 7)) {
        board[fromX][fromY] = Piece(promotionType, turn, 9); 
    //  when the move is made it will be with a queen
    }
    // If en passant, remove the capture pawn
    if (board[fromX][fromY].type == PAWN && fromY != toY && board[toX][toY].type == EMPTY) {
        board[toX + turn][toY] = Piece(EMPTY, 0, 0);
    }
    if (board[fromX][fromY].type == KING && abs(fromY - toY) == 2) {
        // If castling, also move the rook
        if (toY > fromY) {
            // Kingside
            forceMove(fromX, 7, fromX, toY - 1);
        } else {
            // Queenside
            forceMove(fromX, 0, fromX, toY + 1);
        }
    }
    
    forceMove(fromX, fromY, toX, toY); // Make the move on the board

    // Set enPassant flag at the destination square if the move was a pawn move of two squares
    if (board[toX][toY].type == PAWN) {
        if (toX - fromX == 2 || toX - fromX == -2) {
            board[toX][toY].enPassant = 1;
        }
    }
    // Update turn
    if (turn == 1) {
        turn = -1;
    } else {
        turn = 1;
    }
}

vector<pair<int, int>> VecBoard::getValidMoves(int x, int y) {
    // Returns a vector of valid moves for a piece at position (x, y)
    Piece piece = board[x][y];
    vector<pair<int, int>> moves;
    vector<pair<int, int>> validDirections;
    pair<int, int> pieceToKingDiff;
    pair<int, int> pieceToKingDirection;
    int isPinned = 0;
    int dxKnight[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dyKnight[] = {1, 2, 2, 1, -1, -2, -2, -1};
    switch (piece.type) {
        case EMPTY:
            throw invalid_argument("MoveError: getValidMoves called on an empty square\n");
        case KING:
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    if (isMoveInBounds(x + i, y + j) && board[x + i][y + j].color != piece.color) {
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
            // This pin code for the knight and rook (which needs to be added for other pieces)
            // should be migrates into a seperate file called move.cpp and it needs to be split into helper functions 

            // Check for possibility of a pin (a ray from this piece to same color king)
            // -------------------------------------------------------------------------
            isPinned = 0;
            if (verbose) {
                cout << "KNIGHT at (x, y): " << x << ", " << y << endl;
            }
            // 1. Find the king
            for (int tx = 0; tx < 8; tx++) {
                for (int ty = 0; ty < 8; ty++) {
                    if (board[tx][ty].type == KING && board[tx][ty].color == piece.color) {
                        pieceToKingDiff = {tx - x, ty - y};
                        break;
                    }
                }
            }
            // 2. Check if pieceToKingDiff is an actual line on the chess board
            if (pieceToKingDiff.first != 0 && pieceToKingDiff.second != 0 
                && abs(pieceToKingDiff.first) != abs(pieceToKingDiff.second)) {
                // There is no possible pin, any direction is possible
                validDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            } else {// Pin is possible along pieceToKingDiff
                // 3. Iterate down -pieceToKingDirection and check if there is a piece that can pin
                // (queen or rook if pieceToKingDirection is horizontal or vertical and queen or bishop otherwise)

                int dx = (pieceToKingDiff.first > 0) - (pieceToKingDiff.first < 0);
                int dy = (pieceToKingDiff.second > 0) - (pieceToKingDiff.second < 0);
                
                // But first, let's look in direction to king for obstructing pieces
                int newX = x + dx;
                int newY = y + dy;
                while (isMoveInBounds(newX, newY) && board[newX][newY].type == EMPTY) {
                    newX += dx;
                    newY += dy;
                }
                if (board[newX][newY].color != piece.color || board[newX][newY].type != KING) {
                    // Then the pin is obstructed
                    validDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                } else { // Check for a piece that can pin
                    newX = x - dx;
                    newY = y - dy;
                    while (isMoveInBounds(newX, newY) && board[newX][newY].color != piece.color) {
                        if (board[newX][newY].type != EMPTY) {
                            if (board[newX][newY].type == QUEEN || (board[newX][newY].type == ROOK && (dx == 0 || dy == 0)) || (board[newX][newY].type == BISHOP && (dx != 0 && dy != 0))) {
                                isPinned = 1;
                            } else {// The pin is obstructed
                                break;
                            }
                        }
                        newX -= dx;
                        newY -= dy;
                    }
                }
            }
            if (!isPinned) {
                for (int i = 0; i < 8; i++) {
                    int newX = x + dxKnight[i];
                    int newY = y + dyKnight[i];
                    if (isMoveInBounds(newX, newY)) {
                        moves.push_back({newX, newY});
                    }
                }
            } else {
                moves = {};
            }
            break;
        case ROOK:
            if (verbose) {
                cout << "ROOK at (x, y): " << x << ", " << y << endl;
            }
            // Check for possibility of a pin (a ray from this piece to same color king)
            // -------------------------------------------------------------------------
            validDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            // 1. Find the king
            for (int tx = 0; tx < 8; tx++) {
                for (int ty = 0; ty < 8; ty++) {
                    if (board[tx][ty].type == KING && board[tx][ty].color == piece.color) {
                        pieceToKingDiff = {tx - x, ty - y};
                        break;
                    }
                }
            }

            // 2. Check if pieceToKingDiff is an actual line on the chess board
            if (pieceToKingDiff.first != 0 && pieceToKingDiff.second != 0
                && abs(pieceToKingDiff.first) != abs(pieceToKingDiff.second)) {
                // There is no possible pin, any direction is possible
                validDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            } else {// Pin is possible along pieceToKingDiff
                // 3. Iterate down -pieceToKingDirection and check if there is a piece that can pin
                // (queen or rook if pieceToKingDirection is horizontal or vertical and queen or bishop otherwise)

                int dx = (pieceToKingDiff.first > 0) - (pieceToKingDiff.first < 0);
                int dy = (pieceToKingDiff.second > 0) - (pieceToKingDiff.second < 0);

                // But first, let's look in direction to king for obstructing pieces
                int newX = x + dx;
                int newY = y + dy;
                while (isMoveInBounds(newX, newY) && board[newX][newY].type == EMPTY) {
                    newX += dx;
                    newY += dy;
                }
                if (board[newX][newY].color != piece.color || board[newX][newY].type != KING) {
                    // Then the pin is obstructed
                    validDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                } else { // Check for a piece that can pin
                    newX = x - dx;
                    newY = y - dy;
                    while (isMoveInBounds(newX, newY) && board[newX][newY].color != piece.color) {
                        if (board[newX][newY].type != EMPTY) {
                            if (board[newX][newY].type == QUEEN || (board[newX][newY].type == ROOK && (dx == 0 || dy == 0)) || (board[newX][newY].type == BISHOP && (dx != 0 && dy != 0))) {
                                // Then the rook can only move towards the queen or rook, and if it's on a diagonal then it cannot move
                                if (dx == 0 || dy == 0) {
                                    validDirections = {{dx, dy}, {-dx, -dy}};
                                    break;
                                } else {
                                    validDirections = {};
                                    break;
                                }
                                break;
                            }
                            break;
                        }
                        newX -= dx;
                        newY -= dy;
                    }
                }
            }

            for (auto direction : validDirections) {
                int dx = direction.first;
                int dy = direction.second;
                if (verbose) {
                    cout << "dy, dx: " << dy << " " << dx << endl;
                }
                int newX = x + dx;
                int newY = y + dy;
                while (isMoveInBounds(newX, newY) && board[newX][newY].color != piece.color) {
                    if (verbose) {
                        cout << "Possible move: " << newX << ", " << newY << endl;
                    }
                    moves.push_back({newX, newY});
                    if (board[newX][newY].type != EMPTY) {
                        break;// If the square is occupied, stop the loop
                    }

                    newX += dx;
                    newY += dy;
                }
            }
            break;
        case BISHOP:
            if (verbose) {
                cout << "BISHOP at (x, y): " << x << ", " << y << endl;
            }
            for (int dx = -1; dx <= 1; dx += 2) {
                for (int dy = -1; dy <= 1; dy += 2) {
                    // cout << "\ndx:" << dx << " dy:" << dy << endl;
                    int newX = x + dx;
                    int newY = y + dy;

                    while (isMoveInBounds(newX, newY) && board[newX][newY].color != piece.color) {
                        // cout << "Possible move: " << newX << ", " << newY << endl;
                        moves.push_back({newX, newY});
                        if (board[newX][newY].type != EMPTY) {
                            break;// If the square is occupied, stop the loop
                        }
                        newX += dx;
                        newY += dy;
                        // cout << "newX, newY: " << newX << ", " << newY << endl;
                    }
                }
            }
            break;
        case QUEEN:
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
            // en passant check
            if (x == 3 && board[x][y].color == 1) {
                if (y > 0 && board[x][y - 1].enPassant) {
                    moves.push_back({x - 1, y - 1});
                }
                if (y < 7 && board[x][y + 1].enPassant) {
                    moves.push_back({x - 1, y + 1});
                }
            } else if (x == 4 && board[x][y].color == -1) {
                if (y > 0 && board[x][y - 1].enPassant) {
                    moves.push_back({x + 1, y - 1});
                }
                if (y < 7 &&  board[x][y + 1].enPassant) {
                    moves.push_back({x + 1, y + 1});
                }
            }
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

pair<pair<int, int>, pair<int, int>> VecBoard::sanToIndices(const string& sanIn) {
    string san = sanIn;

    if (san == "1-0" || san == "0-1" || san == "1/2-1/2" || san == "*") {
        cout << "WARNING: Game result entered. This should be handled with higher order logic.\n"
             << endl;
        return make_pair(make_pair(-1, -1), make_pair(-1, -1));
    }

    if (verbose) {
        cout << "sanToIndices(" << san << ")" << endl;
        cout << "Turn: " << turn << endl;
    }

    map<char, int> fileToCol = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
    int isCheck = 0;
    if (san.back() == '+') {// this condition is modifies san, needs to be at top
        san = san.substr(0, san.length() - 1);
        isCheck = 1;
    }
    if (san.back() == '#') {
        san = san.substr(0, san.length() - 1);
        // checkmate, possibly add a flag for this
    }
    int destRow = 8 - (san[san.length() - 1] - '0');
    int destCol = fileToCol[san[san.length() - 2]];
    map<char, PieceType> charToPieceType = {{'r', ROOK}, {'n', KNIGHT}, {'b', BISHOP}, {'q', QUEEN}, {'k', KING}, {'R', ROOK}, {'N', KNIGHT}, {'B', BISHOP}, {'Q', QUEEN}, {'K', KING}, {'p', PAWN}, {'P', PAWN}, {'a', PAWN}, {'b', PAWN}, {'c', PAWN}, {'d', PAWN}, {'e', PAWN}, {'f', PAWN}, {'g', PAWN}, {'h', PAWN}};
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

    // if san[-2] = '=' then its a pawn promotion b8=Q, dxe1=Q, ...
    // not handling non queen promotions atm
    else if (san[san.size() - 2] == '=') {
        if (verbose) {
            cout << endl
                 << "San characteristic: san[-2] = '='\n";
        }
        int fromCol = fileToCol[san[0]];
        if (san[1] == 'x') {
            destCol = fileToCol[san[2]];
        } else {
            destCol = fileToCol[san[0]];
        }
        
        if (turn == 1) {
            return make_pair(make_pair(1, fromCol), make_pair(0, destCol));
        } else {
            return make_pair(make_pair(6, fromCol), make_pair(7, destCol));
        }
    }

    // Then it's a capture. The first char will indicate the piece type and the next two chars the dest square
    if (san[1] == 'x') {
        if (verbose) {
            cout << endl
                 << "San characteristic: san[1] = 'x'" << endl;
        }

        PieceType piece = charToPieceType[san[0]];
        int fromCol = fileToCol[san[0]];
        if (san[0] >= 'a' && san[0] <= 'h') {
            piece = PAWN;
        } else {
            piece = charToPieceType[san[0]];
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j].type == piece && board[i][j].color == turn) {
                        vector<pair<int, int>> validMoves = getValidMoves(i, j);
                        if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                            return make_pair(make_pair(i, j), make_pair(destRow, destCol));
                        }
                    }
                }
            }
        }

        int destRow = 8 - static_cast<int>(san[3] - '0');
        int destCol = fileToCol[san[san.length() - 2]];

        for (int k = 0; k < 8; k++) {
            if (board[k][fromCol].type == piece) {
                vector<pair<int, int>> validMoves = getValidMoves(k, fromCol);
                if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                    return make_pair(make_pair(k, fromCol), make_pair(destRow, destCol));
                }
            }
        }
    }

    // If san length is 2, then it's a pawn move: e5, d4, g3, ...
    if (san.length() == 2) {
        if (verbose) {
            cout << endl
                 << "San characteristic: |san| = 2" << endl;
        }
        if (turn == 1) {
            for (int k = destRow; k < 8; k++) {
                Piece currPiece = board[k][destCol];
                if (currPiece.type == PAWN && currPiece.color == turn) {
                    int fromRow = k;
                    int fromCol = destCol;
                    return make_pair(make_pair(fromRow, fromCol), make_pair(destRow, destCol));
                }
            }
        } else {
            for (int k = destRow; k >= 0; k--) {
                Piece currPiece = board[k][destCol];
                if (currPiece.type == PAWN && currPiece.color == turn) {
                    int fromRow = k;
                    int fromCol = destCol;
                    return make_pair(make_pair(fromRow, fromCol), make_pair(destRow, destCol));
                }
            }
        }
    }

    // If san length is 3, then it's a piece move: Nf3, Bb5, Re1, ...
    else if (san.length() == 3) {
        if (verbose) {
            cout << endl
                 << "San characteristic: |san| = 3" << endl;
        }
        PieceType piece = charToPieceType[san[0]];
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j].type == piece && board[i][j].color == turn) {
                    vector<pair<int, int>> validMoves = getValidMoves(i, j);
                    if (verbose) {
                        cout << "destRow:" << destRow << " destCol:" << destCol << endl;
                        cout << i << " " << j << endl
                             << "Valid moves: " << endl;
                    }

                    for (auto move : validMoves) {
                        if (verbose) {
                            cout << move.first << " " << move.second << endl;
                        }
                        if (move.first == destRow && move.second == destCol) {
                            return make_pair(make_pair(i, j), make_pair(destRow, destCol));
                        }
                    }
                    if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                        return make_pair(make_pair(i, j), make_pair(destRow, destCol));
                    }
                }
            }
        }
    }

    // If san length is 4, then it's a capture: Nxf3, Bxb5 or ambiguous move: Nbd7, R1e2, or pawn promotion: e8=Q
    // Capture and promotion cases have already checked.
    // Here ambiguous move: Nbd7, R1e2
    else if (san.length() == 4) {
        if (verbose) {
            cout << endl
                 << "San characteristic: |san| = 4" << endl;
        }
        PieceType piece = charToPieceType[san[0]];

        // Check if ambiguity is along column (san[1] in {a-h})
        //                             or row (san[1] in {0-7})
        if (san[1] >= '1' && san[1] <= '8') {
            int fromRow = 8 - (san[1] - '0');
            for (int k = 0; k < 8; k++) {
                if (board[fromRow][k].type == piece && board[fromRow][k].color == turn) {
                    vector<pair<int, int>> validMoves = getValidMoves(fromRow, k);
                    if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                        return make_pair(make_pair(fromRow, k), make_pair(destRow, destCol));
                    }
                }
            }
        } else {  // then san[1] is a-h
            int fromCol = fileToCol[san[1]];
            for (int k = 0; k < 8; k++) {
                if (board[k][fromCol].type == piece && board[k][fromCol].color == turn) {
                    vector<pair<int, int>> validMoves = getValidMoves(k, fromCol);
                    if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                        return make_pair(make_pair(k, fromCol), make_pair(destRow, destCol));
                    }
                }
            }
        }
    }

    // if |san[2] = 'x' then it's an ambiguous capture
    else if (san[2] == 'x') {
        if (verbose) {
            cout << endl
                 << "San characteristic: san[2] = 'x'" << endl;
        }
        PieceType piece = charToPieceType[san[0]];

        // Check if ambiguity is along column (san[1] in {a-h})
        //                             or row (san[1] in {0-7})
        if (san[1] >= '1' && san[1] <= '8') {
            cout << "Working thus far: " << piece << endl;
            int fromRow = 8 - (san[1] - '0');
            for (int k = 0; k < 8; k++) {
                cout << k << " " << fromRow << " : " << board[fromRow][k].type << " " << board[fromRow][k].color << endl;
                if (board[fromRow][k].type == piece && board[fromRow][k].color == turn) {
                    
                    vector<pair<int, int>> validMoves = getValidMoves(fromRow, k);
                    if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                        return make_pair(make_pair(fromRow, k), make_pair(destRow, destCol));
                    }
                }
            }
        } else {  // then san[1] is a-h
            int fromCol = fileToCol[san[1]];
            for (int k = 0; k < 8; k++) {
                if (board[k][fromCol].type == piece && board[k][fromCol].color == turn) {
                    vector<pair<int, int>> validMoves = getValidMoves(k, fromCol);
                    if (find(validMoves.begin(), validMoves.end(), make_pair(destRow, destCol)) != validMoves.end()) {
                        return make_pair(make_pair(k, fromCol), make_pair(destRow, destCol));
                    }
                }
            }
        }
        
    }

    cout << "WARNING: Invalid move attempted: " << san << endl;
    return make_pair(make_pair(-1, -1), make_pair(-1, -1));  // Return invalid pairs if no valid move is found
}
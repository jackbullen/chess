#include "Move.h"

std::vector<std::pair<int, int>> Move::getValidMoves(Piece piece, int x, int y) {
    std::vector<std::pair<int, int>> moves;
    int dxKnight[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dyKnight[] = {1, 2, 2, 1, -1, -2, -2, -1};
    switch (piece.type) {
        case KING:
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (isValidPosition(x + i, y + j)) {
                        moves.push_back({x + i, y + j});
                    }
                }
            }
            break;
        case KNIGHT:
            for (int i = 0; i < 8; i++) {
                if (isValidPosition(x + dxKnight[i], y + dyKnight[i])) {
                    moves.push_back({x + dxKnight[i], y + dyKnight[i]});
                }
            }
            break;
        case ROOK:
            for (int i = 0; i < 8; i++) {
                if (isValidPosition(x + i, y)) {
                    moves.push_back({x + i, y});
                }
                if (isValidPosition(x, y + i)) {
                    moves.push_back({x, y + i});
                }
            }
            break;
        case BISHOP:
            for (int i = 0; i < 8; i++) {
                if (isValidPosition(x + i, y + i)) {
                    moves.push_back({x + i, y + i});
                }
                if (isValidPosition(x + i, y - i)) {
                    moves.push_back({x + i, y - i});
                }
                if (isValidPosition(x - i, y + i)) {
                    moves.push_back({x - i, y + i});
                }
                if (isValidPosition(x - i, y - i)) {
                    moves.push_back({x - i, y - i});
                }
            }
            break;
        case QUEEN:
            for (int i = 0; i < 8; i++) {
                if (isValidPosition(x + i, y)) {
                    moves.push_back({x + i, y});
                }
                if (isValidPosition(x, y + i)) {
                    moves.push_back({x, y + i});
                }
                if (isValidPosition(x + i, y + i)) {
                    moves.push_back({x + i, y + i});
                }
                if (isValidPosition(x + i, y - i)) {
                    moves.push_back({x + i, y - i});
                }
                if (isValidPosition(x - i, y + i)) {
                    moves.push_back({x - i, y + i});
                }
                if (isValidPosition(x - i, y - i)) {
                    moves.push_back({x - i, y - i});
                }
            }
            break;
        case PAWN:
            if (piece.isWhite) {
                if (isValidPosition(x, y + 1)) {
                    moves.push_back({x, y + 1});
                }
                if (isValidPosition(x + 1, y + 1)) {
                    moves.push_back({x + 1, y + 1});
                }
                if (isValidPosition(x - 1, y + 1)) {
                    moves.push_back({x - 1, y + 1});
                }
            } else {
                if (isValidPosition(x, y - 1)) {
                    moves.push_back({x, y - 1});
                }
                if (isValidPosition(x + 1, y - 1)) {
                    moves.push_back({x + 1, y - 1});
                }
                if (isValidPosition(x - 1, y - 1)) {
                    moves.push_back({x - 1, y - 1});
                }
            }
            break;
    }

    return moves;
}

bool Move::isValidPosition(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}
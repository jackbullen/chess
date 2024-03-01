#ifndef PIECE_H
#define PIECE_H

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
    int isWhite;
    int value;
    Piece(PieceType type, bool isWhite, int value) : type(type), isWhite(isWhite), value(value) {}
};

#endif
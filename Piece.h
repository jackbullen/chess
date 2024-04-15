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
    int color;
    int value;
    int enPassant;
    Piece(PieceType type, int color, int value) : type(type), color(color), value(value), enPassant(0) {}
};

#endif

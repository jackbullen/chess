#include <gtest/gtest.h>

#include "VecBoard.h"

TEST(VecBoardTest, MoveInBoundsTest) {
    VecBoard board;
    ASSERT_TRUE(board.isMoveInBounds(0, 0));
    ASSERT_TRUE(board.isMoveInBounds(VecBoard::BOARD_SIZE - 1, VecBoard::BOARD_SIZE - 1));
    ASSERT_FALSE(board.isMoveInBounds(-1, 0));
    ASSERT_FALSE(board.isMoveInBounds(0, -1));
    ASSERT_FALSE(board.isMoveInBounds(VecBoard::BOARD_SIZE, 0));
    ASSERT_FALSE(board.isMoveInBounds(0, VecBoard::BOARD_SIZE));
    ASSERT_TRUE(board.isMoveInBounds(0, VecBoard::BOARD_SIZE-1));
}

TEST(VecBoardTest, MoveTest1) {
    VecBoard board;
    ASSERT_NO_THROW(board.move("e4"));
    ASSERT_NO_THROW(board.move("e5"));
    ASSERT_NO_THROW(board.move("c5"));
    ASSERT_NO_THROW(board.move("d5"));
}

TEST(VecBoardTest, GetPieceTest) {
    VecBoard board;
    Piece piece = board.getPiece(0, 0);
    ASSERT_EQ(piece.type, PieceType::ROOK);
    ASSERT_EQ(piece.color, -1);
    piece = board.getPiece(7, 7);
    ASSERT_EQ(piece.type, PieceType::ROOK);
    ASSERT_EQ(piece.color, 1);
    piece = board.getPiece(4, 4);
    ASSERT_EQ(piece.type, PieceType::EMPTY);
}

TEST(VecBoardTest, getValidMovesPawnTest) {
    VecBoard board;
    vector<pair<int, int>> x;
    x = {{2,0}, {3,0}};
    ASSERT_EQ(board.getValidMoves(1,0), x);
    x = {{5,7}, {4,7}};
    ASSERT_EQ(board.getValidMoves(6,7), x);
    board.move("e4");
    x = {{3,4}};
    ASSERT_EQ(board.getValidMoves(4,4), x);
    board.move("Nf6");
    x = {};
    ASSERT_EQ(board.getValidMoves(1,5), x);
    board.move("e5");
    x = {{2,4}, {2,5}};
    ASSERT_EQ(board.getValidMoves(3,4), x);
    board.move("d5");
    x = {{2,3}, {2,4}, {2,5}};
    ASSERT_EQ(board.getValidMoves(3,4), x);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>

#include "VecBoard.h"

TEST(VecBoardTest, ConstructorTest) {
    VecBoard board;
    ASSERT_EQ(board.board.size(), VecBoard::BOARD_SIZE);
    for (const auto& row : board.board) {
        ASSERT_EQ(row.size(), VecBoard::BOARD_SIZE);
    }
}

TEST(VecBoardTest, MoveInBoundsTest) {
    VecBoard board;
    ASSERT_TRUE(board.isMoveInBounds(0, 0));
    ASSERT_TRUE(board.isMoveInBounds(VecBoard::BOARD_SIZE - 1, VecBoard::BOARD_SIZE - 1));
    ASSERT_FALSE(board.isMoveInBounds(-1, 0));
    ASSERT_FALSE(board.isMoveInBounds(0, -1));
    ASSERT_FALSE(board.isMoveInBounds(VecBoard::BOARD_SIZE, 0));
    ASSERT_FALSE(board.isMoveInBounds(0, VecBoard::BOARD_SIZE));
}

TEST(VecBoardTest, MoveTest) {
    VecBoard board;
    ASSERT_NO_THROW(board.move(6, 4, 4, 4));
    ASSERT_NO_THROW(board.move(1, 4, 3, 4));
    ASSERT_NO_THROW(board.move(7, 6, 5, 5));
    ASSERT_NO_THROW(board.move(0, 6, 2, 5));
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
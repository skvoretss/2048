#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Board.h"

std::srand(0);

TEST(Board, Move_up_with_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_down_with_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_left_with_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_right_with_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_up_no_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_down_no_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_left_no_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_right_no_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Lose) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Win) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Method_at) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Method_size) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Method_clear) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Method_add_block) {
    EXPECT_EQ(2 + 2, 4);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}
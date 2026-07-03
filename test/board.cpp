#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <cstdlib>
#include "Board.h"

class TestBoard: public Board {
  public:
    bool operator==(const TestBoard& other) const {
        if (other.size() != size()) return false;

        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = 0; j < size(); ++j) {
                if (at(i, j) != other.at(i, j)) return false;
            }
        }

        return true;
    }

    void print_board() {
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = 0; j < size(); ++j) {
                std::cout << at(i, j) << " ";
            }
            std::cout << "\n";
        }
    }
};

TEST(Board, Move_up_with_changes) {
    TestBoard b, expected_b;

    // move block up
    b.add_block_for_test(3, 0);
    expected_b.add_block_for_test(0, 0);
    b.update_board(1);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    expected_b.clear();

    // cannot move up
    expected_b.add_block_for_test(0, 0);
    b.update_board(1);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    expected_b.clear();

    // join equal blocks
    b.add_block_for_test(3, 0);
    expected_b.add_block_for_test(0, 0, 4);
    b.update_board(1);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    expected_b.clear();

    // not join different blocks
    b.add_block_for_test(3, 0);
    expected_b.add_block_for_test(0, 0, 4);
    expected_b.add_block_for_test(1, 0);
    b.update_board(1);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    expected_b.clear();

    // join 3 equal blocks
    b.add_block_for_test(2, 0, 2);
    b.add_block_for_test(3, 0, 2);
    expected_b.add_block_for_test(0, 0, 4);
    expected_b.add_block_for_test(1, 0, 4);
    expected_b.add_block_for_test(2, 0, 2);
    b.update_board(1);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 8);
    expected_b.clear();

    // join 4 equal blocks
    b.add_block_for_test(0, 1, 2);
    b.add_block_for_test(1, 1, 2);
    b.add_block_for_test(2, 1, 2);
    b.add_block_for_test(3, 1, 2);
    expected_b.add_block_for_test(0, 0, 8);
    expected_b.add_block_for_test(1, 0, 2);
    expected_b.add_block_for_test(0, 1, 4);
    expected_b.add_block_for_test(1, 1, 4);
    b.update_board(1);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 24);
}

TEST(Board, Move_down) {
        TestBoard b, expected_b;

    // move block up
    b.add_block_for_test(0, 0);
    expected_b.add_block_for_test(3, 0);
    b.update_board(2);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    expected_b.clear();

    // cannot move up
    expected_b.add_block_for_test(3, 0);
    b.update_board(2);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    expected_b.clear();

    // join equal blocks
    b.add_block_for_test(0, 0);
    expected_b.add_block_for_test(3, 0, 4);
    b.update_board(2);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    expected_b.clear();

    // not join different blocks
    b.add_block_for_test(0, 0);
    expected_b.add_block_for_test(3, 0, 4);
    expected_b.add_block_for_test(2, 0);
    b.update_board(2);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    expected_b.clear();

    // join 3 equal blocks
    b.add_block_for_test(0, 0, 2);
    b.add_block_for_test(1, 0, 2);
    expected_b.add_block_for_test(3, 0, 4);
    expected_b.add_block_for_test(2, 0, 4);
    expected_b.add_block_for_test(1, 0, 2);
    b.update_board(2);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 8);
    expected_b.clear();

    // join 4 equal blocks
    b.add_block_for_test(0, 1, 2);
    b.add_block_for_test(1, 1, 2);
    b.add_block_for_test(2, 1, 2);
    b.add_block_for_test(3, 1, 2);
    expected_b.add_block_for_test(3, 0, 8);
    expected_b.add_block_for_test(2, 0, 2);
    expected_b.add_block_for_test(3, 1, 4);
    expected_b.add_block_for_test(2, 1, 4);
    b.update_board(2);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 24);
}
/*
TEST(Board, Move_left_with_changes) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(Board, Move_right_with_changes) {
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
*/
int main(int argc, char **argv)
{
    std::srand(0);
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}
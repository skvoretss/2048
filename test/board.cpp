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

TEST(Board, get_min) {
    TestBoard b, expected_b;

    b.add_block_for_test(3, 0, 2);
    EXPECT_EQ(b.get_min(), 0);
}

TEST(Board, get_max) {
    TestBoard b, expected_b;

    b.add_block_for_test(3, 0, 2);
    EXPECT_EQ(b.get_max(), 2);
}

TEST(Board, Move_up) {
    TestBoard b, expected_b;
    bool is_changed;

    // move block up
    b.add_block_for_test(3, 0, 2);
    expected_b.add_block_for_test(0, 0, 2);
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // cannot move up
    expected_b.add_block_for_test(0, 0, 2);
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, false);
    expected_b.clear();

    // join equal blocks
    b.add_block_for_test(3, 0, 2);
    expected_b.add_block_for_test(0, 0, 4);
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // not join different blocks
    b.add_block_for_test(3, 0, 2);
    expected_b.add_block_for_test(0, 0, 4);
    expected_b.add_block_for_test(1, 0, 2);
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 3 equal blocks
    b.add_block_for_test(2, 0, 2);
    b.add_block_for_test(3, 0, 2);
    expected_b.add_block_for_test(0, 0, 4);
    expected_b.add_block_for_test(1, 0, 4);
    expected_b.add_block_for_test(2, 0, 2);
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 8);
    EXPECT_EQ(is_changed, true);
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
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 24);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 2 blocks with equal behind
    b.add_block_for_test(3, 2, 4);
    b.add_block_for_test(2, 2, 2);
    b.add_block_for_test(1, 2, 2);
    expected_b.add_block_for_test(0, 0, 8);
    expected_b.add_block_for_test(1, 0, 2);
    expected_b.add_block_for_test(0, 1, 8);
    expected_b.add_block_for_test(0, 2, 4);
    expected_b.add_block_for_test(1, 2, 4);
    is_changed = b.update_board(Direction::UP);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 36);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();
}

TEST(Board, Move_down) {
    TestBoard b, expected_b;
    bool is_changed;

    // move block down
    b.add_block_for_test(0, 0, 2);
    expected_b.add_block_for_test(3, 0, 2);
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // cannot move down
    expected_b.add_block_for_test(3, 0, 2);
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, false);
    expected_b.clear();

    // join equal blocks
    b.add_block_for_test(0, 0);
    expected_b.add_block_for_test(3, 0, 4);
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // not join different blocks
    b.add_block_for_test(0, 0, 2);
    expected_b.add_block_for_test(3, 0, 4);
    expected_b.add_block_for_test(2, 0, 2);
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 3 equal blocks
    b.add_block_for_test(0, 0, 2);
    b.add_block_for_test(1, 0, 2);
    expected_b.add_block_for_test(3, 0, 4);
    expected_b.add_block_for_test(2, 0, 4);
    expected_b.add_block_for_test(1, 0, 2);
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 8);
    EXPECT_EQ(is_changed, true);
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
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 24);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 2 blocks with equal behind
    b.add_block_for_test(0, 2, 4);
    b.add_block_for_test(1, 2, 2);
    b.add_block_for_test(2, 2, 2);
    expected_b.add_block_for_test(3, 0, 8);
    expected_b.add_block_for_test(2, 0, 2);
    expected_b.add_block_for_test(3, 1, 8);
    expected_b.add_block_for_test(3, 2, 4);
    expected_b.add_block_for_test(2, 2, 4);
    is_changed = b.update_board(Direction::DOWN);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 36);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();
}

TEST(Board, Move_left) {
    TestBoard b, expected_b;
    bool is_changed;

    // move block up
    b.add_block_for_test(0, 3, 2);
    expected_b.add_block_for_test(0, 0, 2);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // cannot move up
    expected_b.add_block_for_test(0, 0, 2);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, false);
    expected_b.clear();

    // join equal blocks
    b.add_block_for_test(0, 3, 2);
    expected_b.add_block_for_test(0, 0, 4);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // not join different blocks
    b.add_block_for_test(0, 3, 2);
    expected_b.add_block_for_test(0, 0, 4);
    expected_b.add_block_for_test(0, 1, 2);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 3 equal blocks
    b.add_block_for_test(0, 3, 2);
    b.add_block_for_test(0, 2, 2);
    expected_b.add_block_for_test(0, 0, 4);
    expected_b.add_block_for_test(0, 1, 4);
    expected_b.add_block_for_test(0, 2, 2);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 8);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 4 equal blocks
    b.add_block_for_test(1, 0, 2);
    b.add_block_for_test(1, 1, 2);
    b.add_block_for_test(1, 2, 2);
    b.add_block_for_test(1, 3, 2);
    expected_b.add_block_for_test(0, 0, 8);
    expected_b.add_block_for_test(0, 1, 2);
    expected_b.add_block_for_test(1, 0, 4);
    expected_b.add_block_for_test(1, 1, 4);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 24);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 2 blocks with equal behind
    b.add_block_for_test(2, 0, 2);
    b.add_block_for_test(2, 1, 2);
    b.add_block_for_test(2, 2, 4);
    expected_b.add_block_for_test(0, 0, 8);
    expected_b.add_block_for_test(0, 1, 2);
    expected_b.add_block_for_test(1, 0, 8);
    expected_b.add_block_for_test(2, 0, 4);
    expected_b.add_block_for_test(2, 1, 4);
    is_changed = b.update_board(Direction::LEFT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 36);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();
}

TEST(Board, Move_right) {
    TestBoard b, expected_b;
    bool is_changed;

    // move block up
    b.add_block_for_test(0, 0, 2);
    expected_b.add_block_for_test(0, 3, 2);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // cannot move up
    expected_b.add_block_for_test(0, 3, 2);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 0);
    EXPECT_EQ(is_changed, false);
    expected_b.clear();

    // join equal blocks
    b.add_block_for_test(0, 0, 2);
    expected_b.add_block_for_test(0, 3, 4);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // not join different blocks
    b.add_block_for_test(0, 0, 2);
    expected_b.add_block_for_test(0, 3, 4);
    expected_b.add_block_for_test(0, 2, 2);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 4);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 3 equal blocks
    b.add_block_for_test(0, 1, 2);
    b.add_block_for_test(0, 0, 2);
    expected_b.add_block_for_test(0, 3, 4);
    expected_b.add_block_for_test(0, 2, 4);
    expected_b.add_block_for_test(0, 1, 2);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 8);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 4 equal blocks
    b.add_block_for_test(1, 0, 2);
    b.add_block_for_test(1, 1, 2);
    b.add_block_for_test(1, 2, 2);
    b.add_block_for_test(1, 3, 2);
    expected_b.add_block_for_test(0, 3, 8);
    expected_b.add_block_for_test(0, 2, 2);
    expected_b.add_block_for_test(1, 3, 4);
    expected_b.add_block_for_test(1, 2, 4);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 24);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();

    // join 2 blocks with equal behind
    b.add_block_for_test(2, 3, 2);
    b.add_block_for_test(2, 2, 2);
    b.add_block_for_test(2, 1, 4);
    expected_b.add_block_for_test(0, 3, 8);
    expected_b.add_block_for_test(0, 2, 2);
    expected_b.add_block_for_test(1, 3, 8);
    expected_b.add_block_for_test(2, 3, 4);
    expected_b.add_block_for_test(2, 2, 4);
    is_changed = b.update_board(Direction::RIGHT);
    EXPECT_EQ(b, expected_b);
    EXPECT_EQ(b.get_score(), 36);
    EXPECT_EQ(is_changed, true);
    expected_b.clear();
}

TEST(Board, Lose) {
    TestBoard b;

    EXPECT_EQ(b.check_win(), 0);

    for (size_t i = 0; i < b.size(); ++i)
        for (size_t j = 0; j < b.size(); ++j)
            b.add_block_for_test(i, j, 2);

    EXPECT_EQ(b.check_win(), 0);

    for (size_t i = 0; i < b.size(); i += 2)
        for (size_t j = 0; j < b.size(); j += 2)
            b.add_block_for_test(i, j, 4);

    for (size_t i = 1; i < b.size(); i += 2)
        for (size_t j = 1; j < b.size(); j += 2)
            b.add_block_for_test(i, j, 4);

    EXPECT_EQ(b.check_win(), -1);
}


TEST(Board, Win) {
    TestBoard b;
    b.add_block_for_test(0, 0, 1024);
    b.add_block_for_test(0, 1, 1024);
    EXPECT_EQ(b.check_win(), 0);
    b.update_board(Direction::LEFT);
    EXPECT_EQ(b.check_win(), 1);
}


int main(int argc, char **argv)
{
    std::srand(0);
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}

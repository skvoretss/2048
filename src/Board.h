#include <vector>
#include <cstdint>
#include <ncurses.h>

class Board {
    std::vector<std::vector<int>> board;
    int score;

  public:
    Board(): board(std::vector(4, std::vector(4, 0))), score(0) {};
    Board(const Board& other): board(other.board), score(other.score) {};

    int check_win() const;
    void add_block(int multiplier = 1);
    bool update_board(int direction);
    int get_score() const{ return score; };
    void clear() { board = std::vector(4, std::vector(4, 0)); score = 0; };
    size_t size() const { return board.size(); };
    int get_max() const;
    int at(size_t i, size_t j) const { return board[i][j]; };
    void add_block_for_test(int i, int j, int val = 2) { board[i][j] = val; };
};
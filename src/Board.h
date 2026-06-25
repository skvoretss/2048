#include <vector>
#include <cstdint>
#include <ncurses.h>

class Board {
    std::vector<std::vector<int>> board;
    int score;

    int get_max() const;

  public:
    Board(): board(std::vector(4, std::vector(4, 0))), score(0) {};
    Board(const Board& other): board(other.board), score(other.score) {};

    int check_win() const;
    void add_block(int multiplier = 1);
    bool update_board(int direction);
    int get_score() { return score; };
    void clear() { board = std::vector(4, std::vector(4, 0)); score = 0; };
    size_t size() { return board.size(); };

    int at(size_t i, size_t j) const { return board[i][j]; };

};
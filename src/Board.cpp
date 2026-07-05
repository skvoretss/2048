#include "Board.h"

void Board::add_block(int multiplier) {
    if (get_min()) return;

    int x = std::rand() % 4; 
    int y = std::rand() % 4; 

    while (board[x][y]) {
        x = std::rand() % 4; 
        y = std::rand() % 4; 
    }

    if (get_max() > 512) multiplier += std::rand() % 2;

    board[x][y] = 2 * multiplier;
}

bool Board::update_board(int direction) {
    bool is_changed = false;
    static int board_size = static_cast<int>(board.size());

    switch(direction) {
        case UP:
            for (int i = 0; i != board_size; ++i) {
                int n = 0;
                std::vector<int> v(board_size, 0);

                for (int j = 0; j < board_size; ++j) {
                    if (board[j][i]) {
                        if (n > 0 && v[n - 1] == board[j][i]) {
                            v[n - 1] *= 2;
                            score += v[n - 1];
                        }
                        else {
                            v[n] = board[j][i];
                            ++n;
                        }
                    }
                }

                for (int j = 0; j != board_size; ++j) {
                    if (board[j][i] != v[j]) {
                        is_changed = true;
                        break;
                    }
                }

                if (is_changed) 
                    for (int j = 0; j != board_size; ++j)
                        board[j][i] = v[j];
            }
            break;
        case DOWN:
            for (int i = 0; i < board_size; ++i) {
                int n = board_size - 1;
                std::vector<int> v(board_size, 0);

                for (int j = board_size - 1; j >= 0; --j) {
                    if (board[j][i]) {
                        if (n < board_size - 1 && v[n + 1] == board[j][i]) { 
                            v[n + 1] *= 2;
                            score += v[n + 1];

                        }
                        else {
                            v[n] = board[j][i];
                            --n;
                        }
                    }
                }

                for (int j = board_size - 1; j >= 0; --j) {
                    if (board[j][i] != v[j]) {
                        is_changed = true;
                        break;
                    }
                }

                if (is_changed)
                    for (int j = board_size - 1; j >= 0; --j)
                        board[j][i] = v[j];
            }
            break;
        case LEFT:
            for (int i = 0; i != board_size; ++i) {
                size_t n = 0;
                std::vector<int> v(board_size, 0);

                for (int j = 0; j != board_size; ++j) {
                    if (board[i][j]) {
                        if (n > 0 && v[n - 1] == board[i][j]) {
                            v[n - 1] *= 2;
                            score += v[n - 1];
                        }
                        else {
                            v[n] = board[i][j];
                            ++n;
                        }
                    }
                }

                for (int j = 0; j != board_size; ++j) {
                    if (board[i][j] != v[j]) {
                        is_changed = true;
                        break;
                    }
                }

                if (is_changed) 
                    board[i] = v;
            }
            break;
        case RIGHT:
            for (int i = 0; i != board_size; ++i) {
                int n = board_size - 1;
                std::vector<int> v(board_size, 0);

                for (int j = board_size - 1; j >= 0; --j) {
                    if (board[i][j]) {
                        if (n < board_size - 1 && v[n + 1] == board[i][j]) {
                            v[n + 1] *= 2;
                            score += v[n + 1];
                        }
                        else {
                            v[n] = board[i][j];
                            --n;
                        }
                    }
                }

                for (int j = 0; j != board_size; ++j) {
                    if (board[i][j] != v[j]) {
                        is_changed = true;
                        break;
                    }
                }

                if (is_changed) 
                    board[i] = v;
            }
            break;
    }

    return is_changed;
}

int Board::check_win() const {
    if (get_max() == 2048) return 1;

    static std::vector dx = {0, 1, 0, -1};
    static std::vector dy = {1, 0, -1, 0};

    int status = -1;

    for (int i = 0; i < static_cast<int>(board.size()); ++i) {
        for (int j = 0; j < static_cast<int>(board.size()); ++j) {
            if (board[i][j] == 0) {
                status = 0;
                break;
            }
            else {
                for (int k = 0; k < 4; ++k) {
                    int tx = i + dx[k], ty = j + dy[k];

                    if (tx >= 0 && tx < static_cast<int>(board.size()) && ty >= 0 && ty < static_cast<int>(board.size())) {
                        if (board[i][j] == board[tx][ty]) {
                            status = 0;
                            break;
                        }
                    }
                }
            }
        }

    }

    return status;
}

int Board::get_max() const {
    int cur_max = 0;

    for (const auto& row: board) 
        for (const auto& val: row) 
            cur_max = std::max(val, cur_max);
    
    return cur_max;

}

int Board::get_min() const {
    int cur_min = board[0][0];

    for (const auto& row: board) 
        for (const auto& val: row) 
            cur_min = std::min(val, cur_min);
    
    return cur_min;

}

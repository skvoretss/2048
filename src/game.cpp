#include <ncurses.h>
#include "game.h"

WINDOW *main_wnd;
WINDOW *game_wnd;
WINDOW *score_wnd;
WINDOW *info_wnd;

Area screen_area;
Area game_area;
Area score_area;
Area info_area;

Board b;

int init() {
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //init windows
    screen_area = Area();
    game_area = Area({screen_area.width() / 2 - 2, screen_area.height() - 2}, {1, 1});
    score_area = Area({screen_area.width() / 2 - 2, screen_area.height() / 4 - 2}, {game_area.width() + 2, 1});
    info_area = Area({screen_area.width() / 2 - 2, screen_area.height() / 4 * 3 - 2}, {game_area.width() + 2, score_area.height() + 2});

    main_wnd = newwin(screen_area.height(), screen_area.width(), screen_area.y(), screen_area.x());
    game_wnd = newwin(game_area.height(), game_area.width(), game_area.y(), game_area.x());
    score_wnd = newwin(score_area.height(), score_area.width(), score_area.y(), score_area.x());
    info_wnd = newwin(info_area.height(), info_area.width(), info_area.y(), info_area.x());

    keypad(main_wnd, TRUE);

    //init colors
    if (!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    start_color();
    init_colors();
    init_color_pairs();

    wbkgd(game_wnd, COLOR_PAIR(1));
    wbkgd(info_wnd, COLOR_PAIR(5));
    wbkgd(score_wnd, COLOR_PAIR(3));
    wbkgd(main_wnd, COLOR_PAIR(1));

    box(info_wnd, 0, 0);
    box(score_wnd, 0, 0);
    box(main_wnd, 0, 0);

    wrefresh(main_wnd);
    wrefresh(game_wnd);
    wrefresh(score_wnd);
    wrefresh(info_wnd);

    //place text
    place_info();
    update_score();

    //init board
    b = Board();

    return 0;
}
void init_colors() {
    init_color(COLOR_LIGHT_YELLOW, 255, 255, 224); // 2
    init_color(COLOR_LIGT_YELLOW_GREEN, 222, 249, 117); // 4
    init_color(COLOR_PALE_GREEN, 152, 251, 152); // 8
    init_color(COLOR_MEDIUM_SPRING_GREEN, 0, 250, 154); // 16
    init_color(COLOR_SPRING_GREEN, 0, 255, 127); // 32
    init_color(COLOR_GREEN_YELLOW, 173, 255, 47); // 56
    init_color(COLOR_LAWN_GREEN, 124, 252, 0); // 128
    init_color(COLOR_LIME, 0, 255, 0); // 256
    init_color(COLOR_LIME_GREEN, 50, 205, 50); // 512
    init_color(COLOR_NEON_GREEN, 27, 251, 68); // 1024
    init_color(COLOR_MINT, 9, 255, 110); // 2048

    init_color(COLOR_LINES, 127, 255, 0); // lines
    init_color(COLOR_MAIN_TEXT, 122, 255, 46); // main text
    init_color(COLOR_INFO_TEXT, 185, 253, 146); // info text
    init_color(COLOR_WIN_TEXT, 37, 255, 81); // win text
    init_color(COLOR_LOSS_TEXT, 247, 51, 51); // loss text
}

void init_color_pairs() {
    init_pair(1, COLOR_LINES, COLOR_BLACK);
    init_pair(3, COLOR_MAIN_TEXT, COLOR_BLACK);
    init_pair(5, COLOR_INFO_TEXT, COLOR_BLACK);
    init_pair(7, COLOR_WIN_TEXT, COLOR_BLACK);
    init_pair(9, COLOR_LOSS_TEXT, COLOR_BLACK);

    init_pair(2, COLOR_LIGHT_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_LIGT_YELLOW_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_PALE_GREEN, COLOR_BLACK);
    init_pair(16, COLOR_MEDIUM_SPRING_GREEN, COLOR_BLACK);
    init_pair(32, COLOR_SPRING_GREEN, COLOR_BLACK);
    init_pair(64, COLOR_GREEN_YELLOW, COLOR_BLACK);
    init_pair(128, COLOR_LAWN_GREEN, COLOR_BLACK);
    init_pair(256, COLOR_LIME, COLOR_BLACK);
    init_pair(512, COLOR_LIME_GREEN, COLOR_BLACK);
    init_pair(1024, COLOR_NEON_GREEN, COLOR_BLACK);
    init_pair(2048, COLOR_MINT, COLOR_BLACK);

}

void run() {
    b.add_block();
    redraw_game();
    int in_char;
    bool exit_requested = false, restart_requested = false;
    bool is_changed = false;

    while(1) {
        in_char = wgetch(main_wnd);
        in_char = tolower(in_char);
        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case 'r':
                restart_requested = true;
                break;
            case KEY_UP:
            case 'w':
            case 'i':
                is_changed = b.update_board(UP);
                break;
            case KEY_DOWN:
            case 's':
            case 'k':
                is_changed = b.update_board(DOWN);
                break;
            case KEY_LEFT:
            case 'a':
            case 'j':
                is_changed = b.update_board(LEFT);
                break;
            case KEY_RIGHT:
            case 'd':
            case 'l':
                is_changed = b.update_board(RIGHT);
                break;
            default:
                break;
        }

        if (exit_requested) {
            return quit();
        }

        if (restart_requested) {
            return restart();
        }

        if (is_changed) {
            b.add_block();
            redraw_game();
            update_score();
            int status = b.check_win();

            if (status == 1) {
                return win();
                
            }
            else if (status == -1) {
                return loss();
            }
        }
    }
}

void after_end() {
    bool exit_requested = false, restart_requested = false;
    int in_char;

    while(1) {
        in_char = wgetch(main_wnd);
        in_char = tolower(in_char);
        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case 'r':
                restart_requested = true;
                break;
            default:
                break;
        }

        if (exit_requested) {
            return quit();
        }

        if (restart_requested) {
            return restart();
        }
    }
}

void quit() {
    endwin();
}

void restart() {
    b.clear();
    update_score();
    werase(game_wnd);
    run();
}

void place_info() {
    static std::string banner_1 = " ____   ___  _  _    ___";  
    static std::string banner_2 = "|___ \\ / _ \\| || |  ( _ )"; 
    static std::string banner_3 = "  __) | | | | || |_ / _ \\"; 
    static std::string banner_4 = " / __/| |_| |__   _| (_) |";
    static std::string banner_5 = "|_____|\\___/   |_|  \\___/ ";

    static std::string text_rules = "Join numbers to get the 2048 tile!";
    static std::string text_reset = "Press \"q\" to quit and \"r\" to restart";
    mvwprintw(info_wnd, 1, 1, "%s", banner_1.c_str());
    mvwprintw(info_wnd, 2, 1, "%s", banner_2.c_str());
    mvwprintw(info_wnd, 3, 1, "%s", banner_3.c_str());
    mvwprintw(info_wnd, 4, 1, "%s", banner_4.c_str());
    mvwprintw(info_wnd, 5, 1, "%s", banner_5.c_str());
    wattron(info_wnd, A_ITALIC);
    mvwprintw(info_wnd, 7, 1, "%s", text_rules.c_str());
    mvwprintw(info_wnd, 8, 1, "%s", text_reset.c_str());
    wattroff(info_wnd, A_ITALIC);
    wrefresh(info_wnd);
}

void update_score() {
    werase(score_wnd);
    box(score_wnd, 0, 0);
    static std::string text = "Score";
    wattron(score_wnd, A_ITALIC);
    mvwprintw(score_wnd, 1, 1, "%s", text.c_str());
    std::string value = std::to_string(b.get_score());
    mvwprintw(score_wnd, 2, 1, "%s", value.c_str());
    wattroff(score_wnd, A_ITALIC);
    wrefresh(score_wnd);
}

void redraw_game() {
    werase(game_wnd);
    int board_size = b.size();

    // print frame
    int y = game_area.y(), x = game_area.x();
    wmove(game_wnd, y - 1, x);
    whline(game_wnd, '-', game_area.width());

    for (int i = 0; i < board_size; ++i) {
        y += game_area.height() / board_size;
        wmove(game_wnd, y - 1, x);
        whline(game_wnd, '-', game_area.width()); // horizontal lines
    }

    y = game_area.y();

    for (int i = 0; i < board_size; ++i) {
        x += game_area.width() / board_size;
        wmove(game_wnd, y - 1, x);
        wvline(game_wnd, '|', game_area.height() - 1); // vertical lines
    }

    wmove(game_wnd, game_area.y() - 1, game_area.x());
    wvline(game_wnd, '|', game_area.height() - 1);

    // print nums
    y = game_area.y() + game_area.height() / (board_size * 2);
    x = game_area.x() + game_area.width() / (board_size * 2);

    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            if (b.at(i, j)) {
                auto num = std::to_string(b.at(i, j));
                wattron(game_wnd, COLOR_PAIR(b.at(i, j)));
                mvwprintw(game_wnd, y - 1, x - num.size() / 2, "%s", num.c_str());
                wattroff(game_wnd, COLOR_PAIR(b.at(i, j)));
            }
            x += game_area.width() / board_size;
        }

        y += game_area.height() / board_size;
        x = game_area.x() + game_area.width() / (board_size * 2);
    }

    wrefresh(game_wnd);
}

void win() {
    werase(game_wnd);
    box(game_wnd, 0, 0);
    static std::string text = "You won!";
    wattron(game_wnd, A_BOLD);
    wattron(game_wnd, COLOR_PAIR(7));
    mvwprintw(game_wnd, game_area.height() / 2, (game_area.width() - text.size()) / 2, "%s", text.c_str());
    wattroff(game_wnd, COLOR_PAIR(7));
    wattroff(game_wnd, A_BOLD);
    wrefresh(game_wnd);
    after_end();
}

void loss() {
    werase(game_wnd);
    box(game_wnd, 0, 0);
    static std::string text = "You lost :(";
    wattron(game_wnd, A_BOLD);
    wattron(game_wnd, COLOR_PAIR(9));
    mvwprintw(game_wnd, game_area.height() / 2, (game_area.width() - text.size()) / 2, "%s", text.c_str());
    wattroff(game_wnd, A_BOLD | COLOR_PAIR(9));
    wrefresh(game_wnd);
    after_end();
}
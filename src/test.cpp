#include <iostream>
#include "Board.h"

int main(int argv, char** argc) {

    bool is_changed = false;
    Board b;
    b.add_block();
    for (int i = 0; i != 4; ++i) {
        for (int j = 0; j != 4; ++j) {
            std::cout << b.at(i, j) << " ";
        }
        std::cout << "\n";
    }

    while(1) {
        char in_char;
        std::cin >> in_char;
        switch(in_char) {
            case 'q':
                exit(0);
                break;
            case 'w':
            case 'i':
                is_changed = b.update_board(1);
                break;
            case 's':
            case 'k':
                is_changed = b.update_board(2);
                break;
            case 'a':
            case 'j':
                is_changed = b.update_board(3);
                break;
            case 'd':
            case 'l':
                is_changed = b.update_board(4);
                break;
            default:
                break;
        }

        if (is_changed) {
            b.add_block();
            for (int i = 0; i != 4; ++i) {
                for (int j = 0; j != 4; ++j) {
                   std::cout << b.at(i, j) << " ";
                }
                std::cout << "\n";
            }
        }
    }

    return 0;
}
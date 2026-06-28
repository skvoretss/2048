#pragma once
#include <utility>
#include <string>
#include <cassert>
#include <unistd.h>
#include <cstdlib> 
#include <ctime>
#include "Board.h"
#include "colors.h"

int init();
void run();
void close();
void place_info();
void update_score();
void quit();
void restart();
void redraw_game();
void init_colors();
void init_color_pairs();
void clear_game();
void win();
void loss();

class Area {
    std::pair<uint, uint> size;
    std::pair<uint, uint> start_coors;

  public:
    Area(): size({80, 24}), start_coors({0, 0}) {};
    Area(std::pair<uint, uint> size): size(size), start_coors({0, 0}) {};
    Area(std::pair<uint, uint> size, std::pair<uint, uint> start_coors): size(size), start_coors(start_coors) {};

    uint width() const { return this->size.first; };
    uint height() const { return this->size.second; };

    uint x() const { return this->start_coors.first; };
    uint y() const { return this->start_coors.second; };
};

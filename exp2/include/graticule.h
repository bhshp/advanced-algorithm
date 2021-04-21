#pragma once

#ifndef GRATICULE_H_
#define GRATICULE_H_

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "point.h"

enum point_type {
    NORMAL = 0,
    BARRIER = 1,
    WATER = 2,
    SAND = 4,
    START = 6,
    END = 8
};

struct graticule {
    friend std::istream& operator>>(std::istream& is, graticule& g) {
        is >> g.width_ >> g.height_;
        g.map_.resize(g.height_);
        for (int i = 0; i < g.height_; i++) {
            g.map_[i].resize(g.width_);
            for (int j = 0; j < g.width_; j++) {
                is >> g.map_[i][j];
                switch (g.map_[i][j]) {
                    case point_type::NORMAL:
                    case point_type::BARRIER:
                    case point_type::WATER:
                    case point_type::SAND:
                        break;
                    case point_type::START: {
                        g.start_x_ = i;
                        g.start_y_ = j;
                        break;
                    }
                    case point_type::END: {
                        g.end_x_ = i;
                        g.end_y_ = j;
                        break;
                    }
                    default:
                        assert(false);
                }
            }
        }
        return is;
    }

   public:
    graticule() : width_{-1}, height_{-1}, start_x_{-1}, start_y_{-1}, end_x_{-1}, end_y_{-1} {}
    const std::vector<int>& operator[](size_t index) const {
        return map_[index];
    }

    point start() const { return point{start_x_, start_y_}; }

    point end() const { return point{end_x_, end_y_}; }

    int width() const { return width_; }

    int height() const { return height_; }

   private:
    std::vector<std::vector<int>> map_;
    int width_, height_;
    int start_x_, start_y_;
    int end_x_, end_y_;
};

graticule input_from_file(const char* path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cout << "Path does not exist!" << std::endl;
        return graticule{};
    }
    graticule g;
    in >> g;
    return g;
}

#endif  // GRATICULE_H_

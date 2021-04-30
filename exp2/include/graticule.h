#pragma once

#ifndef GRATICULE_H_
#define GRATICULE_H_

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "color.h"
#include "point.h"
#include "point_type.h"

struct graticule {
    friend std::ostream& operator<<(std::ostream& os, const graticule& g);
    friend std::istream& operator>>(std::istream& is, graticule& g);

   public:
    graticule(const char* path);

    const std::vector<int>& operator[](size_t index) const;

    std::vector<int>& operator[](size_t index);

    point start() const;

    point end() const;

    int width() const;

    int height() const;

    bool in(const point& p) const;

    void save(const char* path) const;

   private:
    std::vector<std::vector<int>> map_;
    int width_, height_;
    int start_x_, start_y_;
    int end_x_, end_y_;
};

std::ostream& operator<<(std::ostream& os, const graticule& g) {
    const static color black{0, 0, 0};
    const int block_length = 20;
    const int line_width = 1;

    int width = g.width() * (block_length + line_width) + line_width,
        height = g.height() * (block_length + line_width) + line_width;
    os << "P3\n" << width << ' ' << height << "\n255\n";

    for (int i = 0; i < line_width; i++) {
        for (int j = 0; j < width; j++) {
            os << black << '\n';
        }
    }

    for (int i = 0; i < g.height(); i++) {
        for (int l = 0; l < block_length; l++) {
            for (int j = 0; j < line_width; j++) {
                os << black << '\n';
            }
            for (int j = 0; j < g.width(); j++) {
                for (int k = 0; k < block_length; k++) {
                    os << [&]() -> const color& {
                        const point &start = g.start(), &end = g.end();
                        bool is_start = i == start.x() && j == start.y(),
                             is_end = i == end.x() && j == end.y();
                        if (!is_start && !is_end) {
                            return color::map.at(
                                static_cast<point_type>(g[i][j]));
                        }
                        bool flag = l * 9 < 2 * block_length ||
                                    l * 9 > 7 * block_length ||
                                    k * 9 < 2 * block_length ||
                                    k * 9 > 7 * block_length;
                        return color::map.at(static_cast<point_type>(
                            flag ? g[i][j] : START_END));
                    }() << '\n';
                }
                for (int k = 0; k < line_width; k++) {
                    os << black << '\n';
                }
            }
        }
        for (int j = 0; j < line_width; j++) {
            for (int k = 0; k < width; k++) {
                os << black << '\n';
            }
        }
    }
    return os << std::flush;
}

std::istream& operator>>(std::istream& is, graticule& g) {
    is >> g.height_ >> g.width_ >> g.start_x_ >> g.start_y_ >> g.end_x_ >>
        g.end_y_;
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
                default:
                    std::cout << i << ' ' << j << std::endl;
                    assert(false);
            }
        }
    }
    return is;
}

graticule::graticule(const char* path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cout << "Path does not exist!" << std::endl;
        return;
    }
    in >> *this;
}

const std::vector<int>& graticule::operator[](size_t index) const {
    return map_[index];
}

std::vector<int>& graticule::operator[](size_t index) { return map_[index]; }

point graticule::start() const { return point{start_x_, start_y_}; }

point graticule::end() const { return point{end_x_, end_y_}; }

int graticule::width() const { return width_; }

int graticule::height() const { return height_; }

bool graticule::in(const point& p) const {
    return p.x() >= 0 && p.x() < height() && p.y() >= 0 && p.y() < width();
}

void graticule::save(const char* path) const {
    std::ofstream{path} << *this << std::flush;
}

#endif  // GRATICULE_H_

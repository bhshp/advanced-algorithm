#pragma once

#ifndef POINT_H_
#define POINT_H_

const double oblique = std::sqrt(2);
const double straight = 1;

struct point {
   public:
    point(int x = 0, int y = 0);
    point operator+(const point &other) const {
        return point{x_ + other.x_, y_ + other.y_};
    }
    int distance(const point &other) const {
        return std::max(std::abs(other.x_ - x_), std::abs(other.y_ - y_));
    }
   private:
    int x_, y_;
};

point::point(int x, int y) : x_{x}, y_{y} {}

point directions[] = {
    point{-1, -1},
    point{-1, 0},
    point{-1, 1},
    point{0, -1},
    point{0, 1},
    point{1, -1},
    point{1, 0},
    point{1, 1}};

double cost[] = {
    oblique,
    straight,
    oblique,
    straight,
    straight,
    oblique,
    straight,
    oblique,
};

#endif  // POINT_H_

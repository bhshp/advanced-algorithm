#pragma once

#ifndef POINT_H_
#define POINT_H_

#include <cmath>
#include <iostream>

const double oblique = std::sqrt(2);

const double straight = 1;

struct point {
    friend std::ostream &operator<<(std::ostream &os, const point &p);

   public:
    point(int x = 0, int y = 0);

    point operator+(const point &other) const;

    bool operator==(const point &other) const;

    bool operator!=(const point &other) const;

    int x() const;

    int y() const;

    double euclidean_distance(const point &other) const;

    double euclidean_distance2(const point &other) const;

    double manhattan_distance(const point &other) const;

    const static point directions[8];

    const static double cost[8];

   private:
    int x_, y_;
};

std::ostream &operator<<(std::ostream &os, const point &p) {
    return os << p.x() << ' ' << p.y();
}

point::point(int x, int y) : x_{x}, y_{y} {}

point point::operator+(const point &other) const {
    return point{x_ + other.x_, y_ + other.y_};
}

bool point::operator==(const point &other) const {
    return x_ == other.x_ && y_ == other.y_;
}

bool point::operator!=(const point &other) const { return !(*this == other); }

int point::x() const { return x_; }

int point::y() const { return y_; }

double point::euclidean_distance(const point &other) const {
    return std::sqrt(euclidean_distance2(other));
}

double point::euclidean_distance2(const point &other) const {
    return pow(other.x_ - x_, 2) + pow(other.y_ - y_, 2);
}

double point::manhattan_distance(const point &other) const {
    return std::max<double>(std::abs(other.x_ - x_), std::abs(other.y_ - y_));
}

const point point::directions[8] = {point{-1, -1}, point{-1, 0}, point{-1, 1},
                                    point{0, -1},  point{0, 1},  point{1, -1},
                                    point{1, 0},   point{1, 1}};

const double point::cost[8] = {
    oblique, straight, oblique, straight, straight, oblique, straight, oblique,
};

#endif  // POINT_H_

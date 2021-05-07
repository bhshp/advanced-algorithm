#pragma once

#ifndef COLOR_H_
#define COLOR_H_

#include <unordered_map>
#include <utility>

#include "graticule.h"
#include "point_type.h"

struct color {
    friend std::ostream &operator<<(std::ostream &os, const color &c);

   public:
    color(int red, int green, int blue);

    uint32_t hash() const;

    bool operator==(const color &other) const;

    color operator*(double x) const;

    const static std::unordered_map<point_type, color> map;

   private:
    int r_, g_, b_;
};

template <>
struct std::hash<color> {
    std::size_t operator()(const color &c) const noexcept {
        return static_cast<std::size_t>(c.hash());
    }
};

int color_cast(int x) {
    if (x < 0) {
        return 0;
    } else if (x > 255) {
        return 255;
    }
    return x;
}

std::ostream &operator<<(std::ostream &os, const color &c) {
    return os << c.r_ << ' ' << c.g_ << ' ' << c.b_;
}

color::color(int red, int green, int blue)
    : r_{color_cast(red)}, g_{color_cast(green)}, b_{color_cast(blue)} {}

uint32_t color::hash() const { return (r_ << 16) | (g_ << 8) | b_; }

bool color::operator==(const color &other) const {
    return hash() == other.hash();
}

color color::operator*(double x) const {
    return color{static_cast<int>(r_ * x), static_cast<int>(g_ * x),
                 static_cast<int>(b_ * x)};
}

const std::unordered_map<point_type, color> color::map{
    {NORMAL, color{255, 255, 255}},   {BARRIER, color{127, 127, 127}},
    {WATER, color{0, 176, 240}},      {SAND, color{255, 192, 0}},
    {START_END, color{63, 194, 112}}, {PATH, color{252, 1, 25}},
    {MID, color{21, 67, 96}},       {OTHER_PATH, color{197, 134, 192}}};

#endif  // COLOR_H_

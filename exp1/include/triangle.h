#pragma once

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "point.h"
#include "util.h"

struct triangle {
   public:
    triangle(const point& a = point{}, const point& b = point{}, const point& c = point{});
    bool in(const point& p) const;

   private:
    point a_, b_, c_;
};

bool point_on_segment(const point& a, const point& b, const point& p);

// Implementation

triangle::triangle(const point& a, const point& b, const point& c) : a_{a}, b_{b}, c_{c} {}

bool triangle::in(const point& p) const {
    int t1 = sgn((b_ - a_) ^ (p - a_)), // AB ^ AP
        t2 = sgn((c_ - b_) ^ (p - b_)), // BC ^ BP
        t3 = sgn((a_ - c_) ^ (p - c_)); // CA ^ CP
    return t1 * t2 >= 0 && t2 * t3 >= 0 && std::abs(t1 + t2 + t3) >= 2;
}

#endif  // TRIANGLE_H_

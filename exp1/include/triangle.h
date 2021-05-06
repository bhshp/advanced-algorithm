#pragma once

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "point2d.h"

struct triangle {
   public:
    triangle(const point2d& a = point2d{}, const point2d& b = point2d{},
             const point2d& c = point2d{});
    bool in(const point2d& p) const;

   private:
    point2d a_, b_, c_;
};

// Implementation

triangle::triangle(const point2d& a, const point2d& b, const point2d& c)
    : a_{a}, b_{b}, c_{c} {}

bool triangle::in(const point2d& p) const {
    static auto sgn = [](double x) -> int {
        const static double eps = 1e-8;
        if (std::fabs(x) < eps) {
            return 0;
        }
        return x > 0 ? 1 : -1;
    };
    int t1 = sgn((b_ - a_) ^ (p - a_)),  // AB ^ AP
        t2 = sgn((c_ - b_) ^ (p - b_)),  // BC ^ BP
        t3 = sgn((a_ - c_) ^ (p - c_));  // CA ^ CP
    return t1 * t2 >= 0 && t2 * t3 >= 0 && std::abs(t1 + t2 + t3) >= 2;
}

#endif  // TRIANGLE_H_

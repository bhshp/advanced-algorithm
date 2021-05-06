#pragma once

#ifndef UTIL_H_
#define UTIL_H_

#include <cmath>

constexpr double eps = 1e-8;

int sgn(double x);

double sqr(double x);

// Implementation

inline int sgn(double x) {
    if (std::fabs(x) < eps) {
        return 0;
    }
    return x > 0 ? 1 : -1;
}

inline double sqr(double x) { return x * x; }

#endif  // UTIL_H_

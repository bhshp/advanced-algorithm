#pragma once

#ifndef UTIL_H_
#define UTIL_H_

#include <algorithm>
#include <cmath>
#include <iterator>
#include <set>
#include <vector>

#include "point.h"
#include "triangle.h"

constexpr double eps = 1e-8;

int sgn(double x);

std::vector<point> enumerate_convex_hull(std::vector<point> v);

// Implementation

inline int sgn(double x) {
    if (std::fabs(x) < eps) {
        return 0;
    }
    return x > 0 ? 1 : -1;
}

inline std::vector<point> enumerate_convex_hull(std::vector<point> v) {
    std::set<point> s;
    for (const point &p : v) {
        s.insert(p);
    }
    int n = v.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    if (triangle{v[j], v[k], v[l]}.in(v[i])) {
                        s.erase(v[i]);
                    } else if (triangle{v[i], v[j], v[k]}.in(v[l])) {
                        s.erase(v[l]);
                    } else if (triangle{v[i], v[k], v[l]}.in(v[j])) {
                        s.erase(v[j]);
                    } else if (triangle{v[i], v[j], v[l]}.in(v[k])) {
                        s.erase(v[k]);
                    }
                }
            }
        }
    }
    std::vector<point> result;
    std::copy(s.begin(), s.end(), std::back_inserter(result));
    return result;
}

#endif  // UTIL_H_

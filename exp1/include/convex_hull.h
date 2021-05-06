#pragma once

#ifndef CONVEX_HULL_H_
#define CONVEX_HULL_H_

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

#include "point2d.h"
#include "triangle.h"

using set_type = std::vector<point2d>;
using function_type = std::function<set_type(set_type)>;

set_type enumerate_convex_hull(set_type v);

set_type graham_scan(set_type v);

set_type divide_and_conquer(set_type v);

// Implementation

inline set_type enumerate_convex_hull(set_type v) {
    int n = v.size();
    std::vector<bool> vis(n, true);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    if (triangle{v[j], v[k], v[l]}.in(v[i])) {
                        vis[i] = false;
                    }
                    if (triangle{v[i], v[k], v[l]}.in(v[j])) {
                        vis[j] = false;
                    }
                    if (triangle{v[i], v[j], v[l]}.in(v[k])) {
                        vis[k] = false;
                    }
                    if (triangle{v[i], v[j], v[k]}.in(v[l])) {
                        vis[l] = false;
                    }
                }
            }
        }
    }
    set_type result;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            result.push_back(v[i]);
        }
    }
    set_type::iterator minimum_pos =
        std::min_element(result.begin(), result.end());
    point2d minimum = *minimum_pos;
    if (minimum_pos != result.begin() && minimum_pos != result.end()) {
        std::swap(*minimum_pos, *result.begin());
    }
    std::sort(result.begin() + 1, result.end(),
              [&minimum](const point2d &a, const point2d &b) -> bool {
                  return ((a - minimum) ^ (b - minimum)) >= 0;
              });
    return result;
}

inline set_type graham_scan(set_type v) {
    if (v.size() < 3) {
        return v;
    }
    set_type::iterator minimum_pos = std::min_element(v.begin(), v.end());
    point2d minimum = *minimum_pos;
    if (minimum_pos != v.begin() && minimum_pos != v.end()) {
        std::swap(*minimum_pos, *v.begin());
    }
    std::sort(v.begin() + 1, v.end(),
              [&minimum](const point2d &a, const point2d &b) -> bool {
                  return ((a - minimum) ^ (b - minimum)) >= 0;
              });
    set_type res;
    for (size_t i = 0; i < v.size(); i++) {
        if (i >= 3) {
            while (!res.empty() && ((v[i] - *(res.rbegin() + 1)) ^
                                    (res.back() - *(res.rbegin() + 1))) > 0) {
                res.pop_back();
            }
        }
        res.push_back(v[i]);
    }
    return res;
}

inline set_type divide_and_conquer(set_type v) {
    std::sort(v.begin(), v.end());
    function_type impl = [&impl](set_type v) -> set_type {
        if (v.size() < 3) {
            return v;
        } else if (v.size() == 3) {
            if (((v[1] - v[0]) ^ (v[2] - v[0])) < 0) {
                std::swap(v[1], v[2]);
            }
            return v;
        }
        int mid = v.size() / 2;
        set_type left = impl(set_type(v.begin(), v.begin() + mid)),
                 right = impl(set_type(v.begin() + mid, v.end()));
        point2d left_most = left[0];
        auto cmp = [&left_most](const point2d &a, const point2d &b) -> bool {
            return ((a - left_most) ^ (b - left_most)) >= 0;
        };
        auto [min_iterator, max_iterator] =
            std::minmax_element(right.begin(), right.end(), cmp);
        set_type counter_clockwise, clockwise;
        auto it = min_iterator;
        while (it != max_iterator) {
            counter_clockwise.push_back(*it);
            if (++it == right.end()) {
                it = right.begin();
            }
        }
        while (it != min_iterator) {
            clockwise.push_back(*it);
            if (++it == right.end()) {
                it = right.begin();
            }
        }
        std::reverse(clockwise.begin(), clockwise.end());
        set_type s{left[0]}, temp;
        std::merge(left.begin() + 1, left.end(), counter_clockwise.begin(),
                   counter_clockwise.end(), std::back_inserter(temp), cmp);
        std::merge(temp.begin(), temp.end(), clockwise.begin(), clockwise.end(),
                   std::back_inserter(s), cmp);
        set_type res;
        for (size_t i = 0; i < s.size(); i++) {
            if (i >= 3) {
                while (s.size() >= 2 &&
                       ((s[i] - *(res.rbegin() + 1)) ^
                        (res.back() - *(res.rbegin() + 1))) > 0) {
                    res.pop_back();
                }
            }
            res.push_back(s[i]);
        }
        return res;
    };
    return impl(v);
}

#endif  // CONVEX_HULL_H_

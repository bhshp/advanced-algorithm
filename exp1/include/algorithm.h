#pragma once

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iterator>
#include <thread>
#include <vector>

#include "point.h"
#include "triangle.h"
#include "util.h"

std::vector<point> enumerate_convex_hull(std::vector<point> v);

std::vector<point> graham_scan(std::vector<point> v);

std::vector<point> divide_and_conquer(std::vector<point> v);

std::vector<point> divide_and_conquer_impl(std::vector<point> v);

// Implementation

inline std::vector<point> enumerate_convex_hull(std::vector<point> v) {
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
    std::vector<point> result;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            result.push_back(v[i]);
        }
    }
    std::cout << "result.size() = " << result.size() << std::endl;
    std::vector<point>::iterator minimum_pos = std::min_element(result.begin(), result.end());
    point minimum = *minimum_pos;
    if (minimum_pos != result.begin() && minimum_pos != result.end()) {
        std::swap(*minimum_pos, *result.begin());
    }
    std::cout << "GEt here" << std::endl;
    std::sort(result.begin() + 1, result.end(), [&minimum](const point &a, const point &b) -> bool {
        return ((a - minimum) ^ (b - minimum)) >= 0;
    });
    return result;
}

inline std::vector<point> graham_scan(std::vector<point> v) {
    if (v.size() < 3) {
        return v;
    }
    std::vector<point>::iterator minimum_pos = std::min_element(v.begin(), v.end());
    point minimum = *minimum_pos;
    if (minimum_pos != v.begin() && minimum_pos != v.end()) {
        std::swap(*minimum_pos, *v.begin());
    }
    std::sort(v.begin() + 1, v.end(), [&minimum](const point &a, const point &b) -> bool {
        return ((a - minimum) ^ (b - minimum)) >= 0;
    });
    std::vector<point> res;
    for (size_t i = 0; i < v.size(); i++) {
        if (i >= 3) {
            while (!res.empty() && ((v[i] - res[res.size() - 2]) ^ (res.back() - res[res.size() - 2])) > 0) {
                res.pop_back();
            }
        }
        res.push_back(v[i]);
    }
    return res;
}

inline std::vector<point> divide_and_conquer(std::vector<point> v) {
    std::sort(v.begin(), v.end());
    return divide_and_conquer_impl(v);
}

inline std::vector<point> divide_and_conquer_impl(std::vector<point> v) {
    if (v.size() < 3) {
        return v;
    } else if (v.size() == 3) {
        if (((v[1] - v[0]) ^ (v[2] - v[0])) < 0) {
            std::swap(v[1], v[2]);
        }
        return v;
    }
    int mid = v.size() / 2;
    std::vector<point> left = divide_and_conquer_impl(std::vector<point>(v.begin(), v.begin() + mid)),
                       right = divide_and_conquer_impl(std::vector<point>(v.begin() + mid, v.end()));
    point left_most = left[0];
    auto cmp = [&left_most](const point &a, const point &b) -> bool {
        if (a == point{3, -1} && b == point{1, 0}) {
            std::cout << (left_most) << std::endl;
            std::cout << (a - left_most) << std::endl;
            std::cout << (b - left_most) << std::endl;
            std::cout << "anser = " << ((a - left_most) ^ (b - left_most)) << std::endl;
        }
        return ((a - left_most) ^ (b - left_most)) >= 0;
    };
    auto [min_iterator, max_iterator] = std::minmax_element(right.begin(), right.end(), cmp);
    std::vector<point> counter_clockwise, clockwise;
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
    std::vector<point> s{left[0]}, temp;
    std::merge(left.begin() + 1, left.end(),
               counter_clockwise.begin(), counter_clockwise.end(),
               std::back_inserter(temp), cmp);
    std::merge(temp.begin(), temp.end(),
               clockwise.begin(), clockwise.end(),
               std::back_inserter(s), cmp);
    std::vector<point> res;
    for (size_t i = 0; i < s.size(); i++) {
        if (i >= 3) {
            while (s.size() >= 2 && ((s[i] - (*(res.rbegin() + 1))) ^ (res.back() - *(res.rbegin() + 1))) > 0) {
                res.pop_back();
            }
        }
        res.push_back(s[i]);
    }
    return res;
}

#endif  // ALGORITHM_H_

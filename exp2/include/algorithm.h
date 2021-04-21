#pragma once

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <functional>
#include <queue>
#include <vector>

#include "graticule.h"

std::vector<point> unidirection_a_star(const graticule &g) {
    point start = g.start(), end = g.end();
    auto cmp = [&end](const point &a, const point &b) -> bool {
        return a.distance(end) < b.distance(end);
    };
    std::priority_queue<point, std::vector<point>, decltype(cmp)> q{cmp};
    q.push(start);
    std::vector<point> result;
    return result;
}

std::vector<point> bidirection_a_star(const graticule &g) {
    point start = g.start(), end = g.end();
    auto cmp = [](const point &p, const point &a, const point &b) -> bool {
        return a.distance(p) < b.distance(p);
    };
    auto cmp1 = std::bind(cmp, end, std::placeholders::_1, std::placeholders::_2);
    auto cmp2 = std::bind(cmp, start, std::placeholders::_1, std::placeholders::_2);
    std::priority_queue<point, std::vector<point>, decltype(cmp1)> q1{cmp1}, q2{cmp2};
    q1.push(start);
    q2.push(end);
    std::vector<point> result;
    return result;
}

#endif  // ALGORITHM_H_

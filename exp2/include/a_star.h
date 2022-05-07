#pragma once

#ifndef A_STAR_H_
#define A_STAR_H_

#include <functional>
#include <limits>
#include <queue>
#include <vector>

#include "graticule.h"
#include "point.h"

#define MANHATTAN

using function_type = std::function<graticule(const graticule &)>;
using node_type = std::pair<double, point>;
using container_type = std::vector<node_type>;
using cmp_type = std::function<double(const node_type &, const node_type &)>;
using queue_type = std::priority_queue<node_type, container_type, cmp_type>;

graticule unidirection_a_star(const graticule &g);

graticule bidirection_a_star(const graticule &g);

// Implementation

graticule unidirection_a_star(const graticule &map) {
    using namespace std;
    if (map.start() == map.end()) {
        return map;
    }
    auto g = [](double x) -> double { return x; };
    auto h = [&map](const point &a) -> double {
        double ratio = 1 - 1e-6;
#if defined(MANHATTAN)
        return ratio * a.manhattan_distance(map.end());
#else
        double x = std::abs(a.x() - map.end().x());
        double y = std::abs(a.y() - map.end().y());
        if (x > y) {
            std::swap(x, y);
        }
        double dis = (y - x) + x * std::sqrt(2);
        return ratio * dis;
#endif
    };
    auto f = [&g, &h](const node_type &a) -> double {
        return g(a.first) + h(a.second);
    };
    auto cmp = [&f](const node_type &a, const node_type &b) -> bool {
        return f(a) > f(b);
    };

    queue_type q{cmp};
    const point dummy = point{-1, -1};
    double sum = 0;

    vector vis(map.height(), vector(map.width(), false));
    vector pre(map.height(), vector(map.width(), dummy));

    vis[map.start().x()][map.start().y()] = true;
    q.emplace(0, map.start());

    while (!q.empty()) {
        const auto [dis, p] = q.top();
        q.pop();
        if (p == map.end()) {
            sum = dis;
            break;
        }
        for (int i = 0; i < 8; i++) {
            point temp = p + point::directions[i];
            if (!map.in(temp) || vis[temp.x()][temp.y()] ||
                map[temp.x()][temp.y()] == point_type::BARRIER) {
                continue;
            }
            vis[temp.x()][temp.y()] = true;
            pre[temp.x()][temp.y()] = p;
            q.emplace(dis + point::cost[i] + map[temp.x()][temp.y()], temp);
        }
    }
    std::cout << "Evaluated: " << sum << std::endl;
    int cnt = 0, all = 0;
    for (size_t i = 0; i < vis.size(); i++) {
        all += vis[i].size();
        for (size_t j = 0; j < vis[i].size(); j++) {
            if (!vis[i][j] && map[i][j] != 1) {
                cnt++;
            }
        }
    }
    std::cout << "Not visited: " << cnt << '/' << all << std::endl;
    graticule result = map;
    point temp = pre[result.end().x()][result.end().y()];
    do {
        result[temp.x()][temp.y()] = PATH;
        temp = pre[temp.x()][temp.y()];
    } while (temp != map.start());
    return result;
}

graticule bidirection_a_star(const graticule &map) {
    using namespace std::placeholders;
    const point start = map.start(), end = map.end();
    if (start == end) {
        return map;
    }
    auto g = [](double x) -> double { return x; };
    auto h = [](const point &a, const point &p) -> double {
        double ratio = 1 - 1e-6;
#if defined(MANHATTAN)
        return ratio * a.manhattan_distance(p);
#else
        double x = std::abs(a.x() - p.x());
        double y = std::abs(a.y() - p.y());
        if (x > y) {
            std::swap(x, y);
        }
        double dis = (y - x) + x * std::sqrt(2);
        return ratio * dis;
#endif
    };
    auto f = [&g, &h](const node_type &a, const point &p) -> double {
        return g(a.first) + h(a.second, p);
    };
    auto cmp = [&f](const node_type &a, const node_type &b,
                    const point &p) -> bool { return f(a, p) > f(b, p); };

    auto cmp1 = std::bind(cmp, _1, _2, end),
         cmp2 = std::bind(cmp, _1, _2, start);

    int height = map.height(), width = map.width();
    const point dummy = point{-1, -1};
    const double inf = std::numeric_limits<double>::infinity();

    queue_type q1{cmp1}, q2{cmp2};
    std::vector vis(height, std::vector(width, 0));
    std::vector pre(height, std::vector(width, dummy));
    std::vector dis(height, std::vector(width, inf));

    vis[start.x()][start.y()] = 1;
    dis[start.x()][start.y()] = 0;
    q1.emplace(0, start);
    vis[end.x()][end.y()] = -1;
    dis[end.x()][end.y()] = 0;
    q2.emplace(0, end);
    point mid_point, left_pre, right_pre;
    double sum = map[end.x()][end.y()];

    while (!q1.empty() && !q2.empty()) {
        bool break_flag = false;
        {
            const auto [dis1, p1] = q1.top();
            q1.pop();
            for (int i = 0; i < 8; i++) {
                point temp = p1 + point::directions[i];
                if (!map.in(temp) || vis[temp.x()][temp.y()] == 1 ||
                    map[temp.x()][temp.y()] == point_type::BARRIER) {
                    continue;
                }
                double cost = dis1 + point::cost[i] + map[temp.x()][temp.y()];
                if (vis[temp.x()][temp.y()] == -1) {
                    sum += cost + dis[temp.x()][temp.y()];
                    mid_point = temp;
                    left_pre = p1;
                    right_pre = pre[temp.x()][temp.y()];
                    break_flag = true;
                    break;
                }
                pre[temp.x()][temp.y()] = p1;
                vis[temp.x()][temp.y()] = 1;
                dis[temp.x()][temp.y()] = cost;
                q1.emplace(cost, temp);
            }
        }
        if (break_flag) {
            break;
        }
        {
            const auto [dis2, p2] = q2.top();
            q2.pop();
            for (int i = 0; i < 8; i++) {
                point temp = p2 + point::directions[i];
                if (!map.in(temp) || vis[temp.x()][temp.y()] == -1 ||
                    map[temp.x()][temp.y()] == point_type::BARRIER) {
                    continue;
                }
                double cost = dis2 + point::cost[i] + map[temp.x()][temp.y()];
                if (vis[temp.x()][temp.y()] == 1) {
                    sum += cost + dis[temp.x()][temp.y()];
                    mid_point = temp;
                    left_pre = pre[temp.x()][temp.y()];
                    right_pre = p2;
                    break_flag = true;
                    break;
                }
                pre[temp.x()][temp.y()] = p2;
                vis[temp.x()][temp.y()] = -1;
                dis[temp.x()][temp.y()] = cost;
                q2.emplace(cost, temp);
            }
        }
        if (break_flag) {
            break;
        }
    }
    std::cout << "Evaluated: " << sum << std::endl;
    int cnt = 0, all = 0;
    for (size_t i = 0; i < vis.size(); i++) {
        all += vis[i].size();
        for (size_t j = 0; j < vis[i].size(); j++) {
            if (!vis[i][j] && map[i][j] != 1) {
                cnt++;
            }
        }
    }
    std::cout << "Not visited: " << cnt << '/' << all << std::endl;
    graticule result = map;
    point temp = left_pre;
    do {
        result[temp.x()][temp.y()] = PATH;
        temp = pre[temp.x()][temp.y()];
    } while (temp != map.start());
    temp = right_pre;
    do {
        result[temp.x()][temp.y()] = OTHER_PATH;
        temp = pre[temp.x()][temp.y()];
    } while (temp != map.end());
    result[mid_point.x()][mid_point.y()] = MID;
    return result;
}

#endif  // A_STAR_H_

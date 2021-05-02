#pragma once

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <set>
#include <vector>

#include "data_generator.h"
#include "glpk_wrapper.h"

int intersection(const set_type &a, const set_type &b) {
    int count = 0;
    size_t first_1 = 0, first_2 = 0, end_1 = a.size(), end_2 = b.size();
    while (first_1 != end_1 && first_2 != end_2) {
        if (a[first_1] == b[first_2]) {
            ++first_1;
            ++first_2;
            ++count;
        } else if (a[first_1] < b[first_2]) {
            ++first_1;
        } else {
            ++first_2;
        }
    }
    return count;
}

set_type greedy_set_cover(const pair_type &p) {
    auto [X, F] = p;
    set_type U = X, C;
    while (!U.empty()) {
        size_t index = 0;
        int ans = 0;
        for (size_t i = 0; i < F.size(); i++) {
            int count = intersection(U, F[i]);
            if (ans < count) {
                ans = count;
                index = i;
            }
        }
        set_type temp;
        std::set_difference(U.begin(), U.end(), F[index].begin(),
                            F[index].end(), std::back_inserter(temp));
        temp.swap(U);
        decltype(temp){}.swap(temp);
        C.push_back(index);
    }
    return C;
}

set_type linear_programming_set_cover(const pair_type &p) {
    auto [X, F] = p;
    assert(!F.empty());
    size_t round = std::log(4 * X.size());
    std::set<int> s;
    size_t row = X.size(), col = F.size();
    std::vector coef(row, std::vector(col, 0.0));
    std::vector obj_coef(col, 1.0);
    std::vector col_bnds(col, limit{bound_type::DOUBLE_BOUND, 0.0, 1.0});
    std::vector row_bnds(row, limit{bound_type::LOWER_BOUND, 1.0, 0.0});
    for (size_t i = 0; i < col; i++) {
        const set_type &set = F[i];
        size_t index = 0;
        for (size_t j = 0; j < row; j++) {
            int val = X[j];
            while (index < set.size() && set[index] < val) {
                ++index;
            }
            if (index == set.size()) {
                break;
            } else if (set[index] == val) {
                coef[j][i] = 1.0;
            }
        }
    }
    std::vector res =
        lin_prog{target_type::MIN, coef, obj_coef, col_bnds, row_bnds}.solve();
    while (round-- > 0) {
        set_type C;
        std::mt19937_64 gen(std::random_device{}());
        std::uniform_real_distribution dis{0.0, 1.0};
        for (size_t i = 1; i < res.size(); i++) {
            double rnd = dis(gen);
            if (rnd < res[i]) {
                s.insert(i - 1);
            }
        }
    }
    return std::vector(s.begin(), s.end());
}

#endif  // ALGORITHM_H_

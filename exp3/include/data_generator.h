#pragma once

#ifndef DATA_GENERATOR_H_
#define DATA_GENERATOR_H_

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using set_type = std::vector<int>;
using set_group_type = std::vector<set_type>;
using pair_type = std::pair<set_type, set_group_type>;

set_type generate_permutation(int num_x);

pair_type generate_F(int num_x, int num_f);

// Implementation

set_type generate_permutation(int num_x) {
    std::vector result(num_x, 0);
    std::iota(result.begin(), result.end(), 0);
    std::shuffle(result.begin(), result.end(),
                 std::mt19937_64{std::random_device{}()});
    return result;
}

pair_type generate_F(int num_x, int num_f) {
    set_type X = generate_permutation(num_x);
    std::mt19937_64 gen{std::random_device{}()};
    const int random_size = 20;
    std::uniform_int_distribution dis{1, random_size};
    set_group_type F(num_f);
    size_t divide = random_size, index = F.size();
    std::copy(X.begin(), X.begin() + divide, std::back_inserter(F[0]));
    for (size_t i = 1; i < F.size(); i++) {
        if (X.size() - divide < 20) {
            F[i].assign(X.begin() + divide, X.end());
            index = i + 1;
            break;
        }
        int size = dis(gen),
            front_size = std::uniform_int_distribution{0, size - 1}(gen),
            back_size = size - front_size;
        std::shuffle(X.begin(), X.begin() + divide, gen);
        std::copy_n(X.begin(), front_size, std::back_inserter(F[i]));
        std::shuffle(X.begin() + divide, X.end(), gen);
        std::copy_n(X.begin() + divide, back_size, std::back_inserter(F[i]));
        divide += back_size;
    }
    std::cout << "At most " << index << " sets are needed" << std::endl;
    for (size_t i = index; i < F.size(); i++) {
        std::shuffle(X.begin(), X.end(), gen);
        std::copy_n(X.begin(), dis(gen), std::back_inserter(F[i]));
    }
    std::sort(X.begin(), X.end());
    std::shuffle(F.begin(), F.end(), gen);
    for (set_type &v : F) {
        std::sort(v.begin(), v.end());
    }
    return std::make_pair(X, F);
}

#endif  // DATA_GENERATOR_H_

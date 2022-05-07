#pragma once

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <vector>

std::vector<int> generate_data(int size, int duplicate_rate) {
    assert(duplicate_rate >= 0 && duplicate_rate <= 10);
    int duplicate = size / 10 * duplicate_rate;
    static std::mt19937_64 gen(std::random_device{}());
    std::vector<int> result(size);
    std::iota(result.begin(), result.end(), 0);
    std::shuffle(std::begin(result), std::end(result), gen);
    int temp = result.front();
    for (int i = 0; i < duplicate; i++) {
        result[i] = temp;
    }
    std::shuffle(std::begin(result), std::end(result), gen);
    return result;
}

#endif  // GENERATOR_H_

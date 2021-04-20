#pragma once

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <fstream>
#include <iostream>
#include <random>

#include "point.h"

void generate_point(const char* path, int n);

// Implementation

void generate_point(const char* path, int n) {
    static std::mt19937_64 gen{std::random_device{}()};
    static std::uniform_real_distribution<double> dis{0, 100};
    std::ofstream out(path);
    if (!out.is_open()) {
        std::cout << "Cannot open " << path << std::endl;
        return;
    }
    out << n << std::endl;
    for (int i = 0; i < n; i++) {
        out << dis(gen) << ' ' << dis(gen) << std::endl;
    }
    out.close();
}

#endif  // GENERATOR_H_

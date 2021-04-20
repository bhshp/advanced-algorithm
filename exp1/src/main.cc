#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "point.h"
#include "util.h"

int main() {
    std::ofstream out("./target/1.out");
    std::ifstream in("./data/1.in");
    if (!in.is_open() || !out.is_open()) {
        std::cout << "Cannot open files" << std::endl;
        return 0;
    }

    int n;
    in >> n;
    std::vector<point> v;
    std::copy_n(std::istream_iterator<point>{in}, n, std::back_inserter(v));

    using namespace std::chrono_literals;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::vector<point> res = enumerate_convex_hull(v);
    std::cout << (std::chrono::high_resolution_clock::now() - start) / 1ms << " ms elapsed" << std::endl;

    std::vector<point>::iterator minimum_pos = std::min_element(res.begin(), res.end());
    point minimum = *minimum_pos;
    if (minimum_pos != res.begin() && minimum_pos != res.end()) {
        std::swap(*minimum_pos, *res.begin());
    }
    std::sort(res.begin() + 1, res.end(), [&minimum](const point &a, const point &b) -> bool {
        return std::atan2(a.y() - minimum.y(), a.x() - minimum.x()) < std::atan2(b.y() - minimum.y(), b.x() - minimum.x());
    });
    out << res.size() << std::endl;
    for (const point &p : res) {
        out << p << std::endl;
    }
    return 0;
}
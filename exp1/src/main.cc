#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "convex_hull.h"
#include "convex_hull_timer.h"
#include "point2d.h"

std::vector<point2d> generate_point(int n) {
    static std::mt19937_64 gen{std::random_device{}()};
    static std::uniform_real_distribution<double> dis{0, 100};
    std::vector<point2d> result;
    std::generate_n(std::back_inserter(result), n, []() -> point2d {
        return point2d{dis(gen), dis(gen)};
    });
    return result;
}

void test(int n, bool save = false, const char *path = nullptr) {
    std::cout << "n = " << n << std::endl;
    using set_type = std::vector<point2d>;
    using function_type = std::function<set_type(set_type)>;

    const static std::vector<function_type> function_list{
        enumerate_convex_hull, graham_scan, divide_and_conquer};
    const static std::vector<std::string> function_name_list{
        "enumerate", "graham_scan", "divide_and_conquer"};
    const size_t size = function_list.size();

    set_type v = generate_point(n);
    for (size_t i = 0; i < size; i++) {
        if (n >= 1000 && i == 0) {
            continue;
        }
        convex_hull_timer t{function_name_list[i]};
        if (!save) {
            function_list[i](v);
        } else {
            set_type s = function_list[i](v);
            assert(path != nullptr);
            std::string current_path = std::string(path)
                                           .append(function_name_list[i])
                                           .append("_")
                                           .append(std::to_string(n))
                                           .append(".txt");
            std::ofstream out(current_path);
            if (!out.is_open()) {
                continue;
            }
            out << v.size() << '\n';
            for (const point2d &p : v) {
                out << p << '\n';
            }
            out << s.size() << '\n';
            for (const point2d &p : s) {
                out << p << '\n';
            }
            out.flush();
            out.close();
        }
    }
    std::cout << std::endl;
}

int main() {
    for (int n : {50, 100, 1000, 2000, 3000, 5000, 10000, 20000, 30000, 50000,
                  100000}) {
        test(n);
    }
    // test(100, true, "./target/"); // only directory
    // test output and paint a picture
    return 0;
}

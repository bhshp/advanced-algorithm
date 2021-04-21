#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "algorithm.h"
#include "point.h"
#include "util.h"

using namespace std;
using namespace chrono_literals;

void test(int index, function<vector<point>(const vector<point> &)> f, const std::string &name) {
    string in_path = "./data/" + to_string(index) + ".in";
    // input and output initialize
    ifstream in(in_path);
    if (!in.is_open()) {
        cout << "Cannot open files" << endl;
        return;
    }
    // input
    int n;
    in >> n;
    vector<point> v;
    copy_n(istream_iterator<point>{in}, n, back_inserter(v));

    // calculate and count time
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    auto res = f(v);
    cout << n << " points using " << name << " algorithm: "
         << (chrono::high_resolution_clock::now() - start) / 1ms << " ms" << endl;

    std::ofstream out("./target/" + std::to_string(index) + ".out");
    out << res.size() << std::endl;
    for (const auto &p : res) {
        out << p << std::endl;
    }
}

int main() {
    for (int i = 1; i <= 5; i++) {
        // test(i, graham_scan, "graham-scan");
        test(i, divide_and_conquer, "divide-and-conquer");
    }
    return 0;
}
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#include "generator.h"
#include "sort.h"

using namespace std;
using namespace chrono;
using namespace chrono_literals;

void test(const string &name, vector<int> data, int i,
          function<void(vector<int> &, int, int)> f) {
    steady_clock::time_point start = steady_clock::now();
    f(data, 0, data.size() - 1);
    steady_clock::time_point now = steady_clock::now();
    cout << name << " sorting " << data.size() << " numbers with " << i * 10
         << "% duplicate numbers cost " << ((now - start) / 1ms) << "ms"
         << endl;
    assert(is_sorted(data.begin(), data.end()));
}

int main() {
#define ENLARGE_STACK

#ifdef ENLARGE_STACK
    const int stack_size = 256 << 20;
    asm("movl %0, %%esp\n" ::"r"((char *)malloc(stack_size) + stack_size));
#endif

    const int size = 1e6;
    for (int i = 0; i <= 10; i++) {
        vector<int> data = generate_data(size, i);
        // test("Naive Quicksort", data, i, naive_quicksort);
        test("Improved Quicksort", data, i, improved_quicksort);
        test("std::sort", data, i, [](vector<int> &data, int, int) -> void {
            std::sort(data.begin(), data.end());
        });
        std::cout << std::endl;
    }
    return 0;
}

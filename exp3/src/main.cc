#include "data_generator.h"
#include "glpk_wrapper.h"
#include "set_cover.h"
#include "timer.h"

int main() {
    std::vector<int> v{100, 1000, 5000};
    for (int x : v) {
        const pair_type &p = generate_F(x, x);
        const auto &vv = p.second;
        int max_count = 0;
        for (int i = 0; i < x; i++) {
            int cnt = 0;
            for (const auto &v : vv) {
                auto it = std::lower_bound(v.begin(), v.end(), i);
                if (it != v.end() && *it == i) {
                    ++cnt;
                }
            }
            max_count = std::max(max_count, cnt);
        }
        std::cout << "max frequency: " << max_count << std::endl;
        {
            timer t;
            set_type result = greedy_set_cover(p);
            std::cout << "Greedy: " << result.size() << std::endl;
        }
        {
            timer t;
            set_type result = linear_programming_set_cover(p);
            std::cout << "Linear Programming: " << result.size() <<
            std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}

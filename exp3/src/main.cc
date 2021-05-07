#include "data_generator.h"
#include "glpk_wrapper.h"
#include "set_cover.h"
#include "timer.h"

int main() {
    std::vector<int> v{100, 1000, 5000};
    for (int x : v) {
        const pair_type &p = generate_F(x, x);
        {
            timer t;
            set_type result = greedy_set_cover(p);
            std::cout << "Greedy: " << result.size() << std::endl;
        }
        {
            timer t;
            set_type result = linear_programming_set_cover(p);
            std::cout << "Linear Programming: " << result.size() << std::endl;
        }
    }
    return 0;
}

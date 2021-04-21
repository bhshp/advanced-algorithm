#include "generator.h"

int main() {
    // point a{1, 1}, b{6, 3}, c{4, 7};
    // point p{4, 5};
    // std::cout.setf(std::ios::boolalpha);
    // std::cout << triangle{a, b, c}.in(p) << std::endl;
    generate_point("./data/1.in", 100);
    generate_point("./data/2.in", 1000);
    generate_point("./data/3.in", 5000);
    generate_point("./data/4.in", 10000);
    generate_point("./data/5.in", 100000);
    return 0;
}

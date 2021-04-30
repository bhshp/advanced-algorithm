#include <iostream>

#include "algorithm.h"
#include "color.h"
#include "graticule.h"
#include "point.h"
#include "timer.h"

// 13.0711
// 67.0416

void test(const char* input_path, double concrete,
          const std::function<graticule(const graticule&)>& f,
          bool save = false, const char* save_path = nullptr) {
    graticule g(input_path);
    std::cout << "Concrete: " << concrete << std::endl;
    timer t;
    if (save) {
        f(g).save(save_path);
    } else {
        f(g);
    }
}

int main() {
    const double result_1 = 13.0711, result_2 = 67.0416;
    test("./data/1.in", result_1, unidirection_a_star, true, "./target/out.ppm");
    test("./data/2.in", result_2, unidirection_a_star);
    test("./data/1.in", result_1, bidirection_a_star);
    test("./data/2.in", result_2, bidirection_a_star);
    return 0;
}

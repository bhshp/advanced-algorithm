#include <iostream>

#include "a_star.h"
#include "a_star_timer.h"
#include "color.h"
#include "graticule.h"
#include "point.h"

void test(const char* input_path, double concrete, const function_type& f,
          bool save = false, const char* save_path = nullptr) {
    graticule g(input_path);
    std::cout << "Concrete: " << concrete << std::endl;
    a_star_timer t;
    if (save) {
        assert(save_path != nullptr);
        f(g).save(save_path);
    } else {
        f(g);
    }
}

int main() {
    const double result_1 = 13.0711, result_2 = 67.0416;
    bool save = true;
    std::cout << "Unidirection A Star" << std::endl;
    test("./data/1.in", result_1, unidirection_a_star, save, "./target/1.ppm");
    test("./data/2.in", result_2, unidirection_a_star, save, "./target/2.ppm");
    std::cout << "Bidirection A Star" << std::endl;
    test("./data/1.in", result_1, bidirection_a_star, save, "./target/3.ppm");
    test("./data/2.in", result_2, bidirection_a_star, save, "./target/4.ppm");
    return 0;
}

#include <iostream>

#include "algorithm.h"
#include "graticule.h"
#include "point.h"

int main() {
    graticule g;
    unidirection_a_star(g);
    bidirection_a_star(g);
    return 0;
}

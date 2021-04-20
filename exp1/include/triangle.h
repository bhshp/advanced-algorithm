#pragma once

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "point.h"

struct triangle {
   public:
    triangle(point a = point{}, point b = point{}, point c = point{});
    bool in(const point &p) const;

   private:
    point a_, b_, c_;
};

triangle::triangle(point a = point{}, point b = point{}, point c = point{}) : a_{a}, b_{b}, c_{c} {}

bool triangle::in(const point &p) const {
    
}

#endif  // TRIANGLE_H_

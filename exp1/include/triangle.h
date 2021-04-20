#pragma once

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "point.h"
#include "util.h"

struct triangle {
   public:
    triangle(const point& a = point{}, const point& b = point{}, const point& c = point{});
    bool in(const point& p) const;

   private:
    point a_, b_, c_;
};

triangle::triangle(const point& a, const point& b, const point& c) : a_{a}, b_{b}, c_{c} {}

bool triangle::in(const point& p) const {
    point pa = a_ - p, pb = b_ - p, pc = c_ - p;
    double ab = pa ^ pb, bc = pb ^ pc, ca = pc ^ pa;
    return ab * bc >= 0 && bc * ca >= 0;
}

#endif  // TRIANGLE_H_

#pragma once

#ifndef CONVEX_HULL_TIMER_H_
#define CONVEX_HULL_TIMER_H_

#include <chrono>
#include <iostream>

struct convex_hull_timer {
   public:
    convex_hull_timer(const std::string &s);
    ~convex_hull_timer();

   private:
    std::chrono::system_clock::time_point start_time_;
    std::string prefix_;
};

inline convex_hull_timer::convex_hull_timer(const std::string &s)
    : start_time_{std::chrono::system_clock::now()}, prefix_{s} {}

inline convex_hull_timer::~convex_hull_timer() {
    using namespace std::chrono_literals;
    std::cout << prefix_ << " cost "
              << (std::chrono::system_clock::now() - start_time_) / 1ms << " ms"
              << std::endl;
}

#endif  // CONVEX_HULL_TIMER_H_

#pragma once

#ifndef A_STAR_TIMER_H_
#define A_STAR_TIMER_H_

#include <chrono>
#include <iostream>

struct a_star_timer {
   public:
    a_star_timer();
    ~a_star_timer();

   private:
    std::chrono::system_clock::time_point start_time_;
};

a_star_timer::a_star_timer() : start_time_{std::chrono::system_clock::now()} {}

a_star_timer::~a_star_timer() {
    using namespace std::chrono_literals;
    std::cout << (std::chrono::system_clock::now() - start_time_) / 1ms
              << " ms\n"
              << std::endl;
}

#endif  // A_STAR_TIMER_H_

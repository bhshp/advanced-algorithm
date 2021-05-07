#pragma once

#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

struct timer {
   public:
    timer();
    ~timer();

   private:
    std::chrono::system_clock::time_point start_time_;
};

timer::timer() : start_time_{std::chrono::system_clock::now()} {}

timer::~timer() {
    using namespace std::chrono_literals;
    std::cout << (std::chrono::system_clock::now() - start_time_) / 1ms
              << " ms"
              << std::endl;
}

#endif  // TIMER_H_

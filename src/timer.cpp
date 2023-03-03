#include "timer.hpp"

Timer::Timer(double limit) : limit_{limit}, start_{clock::now()} {}

void Timer::Reset(double limit) {
    limit_ = limit;
    start_ = clock::now();
}

double Timer::ElapsedSeconds() const {
    return std::chrono::duration_cast<fsec>(clock::now() - start_).count();
}

bool Timer::Expired() const {
    return ElapsedSeconds() >= limit_;
}

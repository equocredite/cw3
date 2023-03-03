#ifndef PARALGO_HW3_TIMER_HPP
#define PARALGO_HW3_TIMER_HPP

#include <chrono>

class Timer {
  public:
    using fsec = std::chrono::duration<double, std::chrono::seconds::period>;
    using clock = std::chrono::steady_clock;
    using time_point = decltype(clock::now());

    explicit Timer(double limit);

    void Reset(double limit);

    [[nodiscard]] double ElapsedSeconds() const;

    [[nodiscard]] bool Expired() const;


  private:
    double limit_;
    time_point start_;
};

#endif //PARALGO_HW3_TIMER_HPP

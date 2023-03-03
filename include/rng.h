#ifndef CW3_GEN_H
#define CW3_GEN_H

#include <random>
#include <ctime>
#include <cstdio>

class Rng {
  public:
    int Uniform(int min, int max) {
        std::uniform_int_distribution<int> uniform{min, max};
        return uniform(random_);
    }

    static int Bernoulli(double p = 0.5) {
        static std::mt19937 random{};
        std::bernoulli_distribution bernoulli{p};
        return bernoulli(random);
    }

  private:
    std::mt19937 random_{};
};

#endif //CW3_GEN_H

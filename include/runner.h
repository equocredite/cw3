#ifndef PARALGO_HW3_RUNNER_H
#define PARALGO_HW3_RUNNER_H

#include "timer.hpp"
#include "rng.h"
#include "validation.hpp"
#include "config.hpp"
#include <thread>
#include <random>
#include <iostream>
#include <set>

class Runner {
  public:
    Runner(size_t n_threads, int threshold, int min_key, int max_key)
            : n_threads_(n_threads)
            , threshold_(threshold)
            , min_key_(min_key)
            , max_key_(max_key) {}

    double RunAndCalcThroughput() {
        std::vector<std::thread> threads;
        std::vector<int> n_operations(n_threads_, 0);
        for (size_t i = 0; i < n_threads_; ++i) {
            threads.emplace_back(&Runner::RunWorker, this, std::ref(n_operations[i]));
        }
        int n_operations_total = 0;
        for (size_t i = 0; i < n_threads_; ++i) {
            threads[i].join();
            n_operations_total += n_operations[i];
        }
        return n_operations_total / 5.0;
    }

    void Prepopulate() {
        std::vector<int> keys;
        for (int key = min_key_; key <= max_key_; ++key) {
            if (Rng::Bernoulli()) {
                keys.push_back(key);
            }
        }
        std::shuffle(keys.begin(), keys.end(), std::mt19937(std::random_device()()));
        for (int key : keys) {
            tree_.Insert(key);
        }
    }

    const Tree& GetTree() const {
        return tree_;
    }

  private:
    void RunWorker(int& n_operations) {
        Timer timer{5.0};
        while (!timer.Expired()) {
            int key = SelectKey();
            int p = SelectP();
            if (p < threshold_) {
                tree_.Insert(key);
            } else if (p < 2 * threshold_) {
                tree_.Erase(key);
            } else {
                tree_.Contains(key);
            }
            ++n_operations;
        }
    }

    int SelectKey() const {
        return rng_.Uniform(min_key_, max_key_);
    }

    static int SelectP() {
        return rng_.Uniform(1, 100);
    }

    const size_t n_threads_;
    const int threshold_;
    const int min_key_;
    const int max_key_;
    static thread_local inline Rng rng_ = Rng{};

    Tree tree_;
};

#endif //PARALGO_HW3_RUNNER_H

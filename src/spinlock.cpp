#include "spinlock.hpp"
#include "validation.hpp"

void SpinLock::Lock() noexcept {
    while (true) {
        if (!locked_.exchange(true, std::memory_order_acquire)) {
            return;
        }
        while (locked_.load(std::memory_order_relaxed)) {}
    }
}

void SpinLock::Unlock() noexcept {
    locked_.store(false, std::memory_order_release);
}

SpinLock::~SpinLock() {
    AssertDebug(!locked_.load(std::memory_order_relaxed), "Attempted to destroy a locked spinlock.");
}

#ifndef CW3_SPINLOCK_HPP
#define CW3_SPINLOCK_HPP

#include <atomic>

class SpinLock {
  public:
    void Lock() noexcept;

    void Unlock() noexcept;

    ~SpinLock();

  private:
    std::atomic<bool> locked_{false};
};

#endif //CW3_SPINLOCK_HPP

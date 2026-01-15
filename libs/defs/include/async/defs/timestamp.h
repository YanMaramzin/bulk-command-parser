#pragma once
#include <chrono>

namespace async::defs {
    using Clock = std::chrono::system_clock;
    using TimePoint = Clock::time_point;

    inline TimePoint now() {
        return Clock::now();
    }
}

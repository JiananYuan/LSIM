//
// Created by yjn on 23-1-4.
//
#include "timer.h"
#include <cassert>
#include <x86intrin.h>
#include "param.h"
#include "stats.h"

namespace mod {
    Timer::Timer(): time_accumulated(0), started(false) {}

    Timer::Timer(std::string _name): time_accumulated(0), started(false), name(_name) {}

    void Timer::setName(std::string _name) {
        name = _name;
    }

    std::string Timer::Name() {
        return name;
    }

    void Timer::Start() {
        assert(!started);
        unsigned int dummy = 0;
        time_started = __rdtscp(&dummy);
        started = true;
    }

    void Timer::Reset() {
        time_accumulated = 0;
        started = false;
    }

    uint64_t Timer::Time() {
        return time_accumulated;
    }

    std::pair<uint64_t, uint64_t> Timer::Pause(bool record) {
        assert(started);
        unsigned int dummy = 0;
        uint64_t time_elapse = __rdtscp(&dummy) - time_started;
        time_accumulated += time_elapse / frequency;
        if (record) {
            Stats* instance = Stats::GetInstance();
            uint64_t start_absolute = time_started - instance->init_time;
            uint64_t end_absolute = start_absolute + time_elapse;
            started = false;
            return {start_absolute / frequency, end_absolute / frequency};
        } else {
            started = false;
            return {0, 0};
        }
    }
}



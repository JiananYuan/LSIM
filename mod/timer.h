//
// Created by yjn on 23-1-4.
//

#ifndef LSIM_TIMER_H
#define LSIM_TIMER_H

#include <cstdint>
#include <iostream>

namespace mod {
    class Timer {
        uint64_t time_started;
        uint64_t time_accumulated;
        bool started;
        std::string name;

    public:
        void Start();
        std::pair<uint64_t, uint64_t> Pause(bool record = false);
        void Reset();
        uint64_t Time();
        void setName(std::string);
        std::string Name();

        Timer();
        Timer(std::string);
        ~Timer() = default;
    };
}

#endif //LSIM_TIMER_H

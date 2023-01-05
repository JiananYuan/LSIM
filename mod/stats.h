//
// Created by yjn on 23-1-4.
//

#ifndef LSIM_STATS_H
#define LSIM_STATS_H
#include <vector>
#include <cstdint>
#include "timer.h"

namespace mod {
    class Timer;
    class Stats {
        static Stats* singleton;
        Stats();
        std::vector<Timer> timers;

    public:
        uint64_t init_time;
        static Stats* GetInstance();
        void StartTimer(uint32_t id);
        std::pair<uint64_t, uint64_t> PauseTimer(uint32_t id, bool record = false);
        void ResetTimer(uint32_t id);
        uint64_t ReportTime(uint32_t id);
        void ReportTime();

        uint64_t GetTime();
        void ResetAll();
        ~Stats();
    };

}

#endif //LSIM_STATS_H

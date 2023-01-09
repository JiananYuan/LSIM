//
// Created by yjn on 23-1-4.
//

#include "stats.h"
#include <x86intrin.h>
#include <cstdio>
#include "param.h"

namespace mod {
    Stats* Stats::singleton = nullptr;

    Stats::Stats() : timers(20, Timer{}), init_time(__rdtsc()) {
        timers[0].setName("二级索引总时间");
        timers[1].setName("主索引总时间");
        timers[2].setName("FindFiles");
        timers[3].setName("SearchIB/DB");
        timers[4].setName("SearchFB");
        timers[5].setName("LoadDB");
        timers[6].setName("ReadValue");
        timers[7].setName("LoadIB/FB");
    }

    Stats* Stats::GetInstance() {
        if (!singleton) singleton = new Stats();
        return singleton;
    }

    void Stats::StartTimer(uint32_t id) {
        Timer& timer = timers[id];
        timer.Start();
    }

    std::pair<uint64_t, uint64_t> Stats::PauseTimer(uint32_t id, bool record) {
        Timer& timer = timers[id];
        return timer.Pause(record);
    }

    void Stats::ResetTimer(uint32_t id) {
        Timer& timer = timers[id];
        timer.Reset();
    }

    uint64_t Stats::ReportTime(uint32_t id) {
        Timer& timer = timers[id];
        printf("Timer %d(%s): %lu\n", id, timer.Name().data(), timer.Time() / 100);
        return timer.Time();
    }

    void Stats::ReportTime() {
        for (int i = 0; i < timers.size(); ++i) {
            printf("Timer %u: %lu\n", i, timers[i].Time());
        }
    }

    uint64_t Stats::GetTime() {
        unsigned int dummy = 0;
        uint64_t time_elapse = __rdtscp(&dummy) - init_time;
        return time_elapse / frequency;
    }

    void Stats::ResetAll() {
        for (Timer& t: timers) t.Reset();
        init_time = __rdtsc();
    }

    Stats::~Stats() {
        ReportTime();
    }
}
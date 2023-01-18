//
// Created by jianan yuan on 2023/1/10.
//

#ifndef LSIM_UTIL_H
#define LSIM_UTIL_H
#include <cstdint>
#include "leveldb/slice.h"

namespace mod {
    uint64_t SliceToInteger(const Slice& slice);
}

#endif //LSIM_UTIL_H

//
// Created by jianan yuan on 2023/1/10.
//

#ifndef LSIM_LEARNED_INDEX_H
#define LSIM_LEARNED_INDEX_H
#include <vector>
#include <map>
#include "rs/multi_map.h"
#include <cstdint>

namespace mod {

    class LearnedIndexData {
    public:

    private:

    };

    class FileLearnedIndexData {
    public:
      std::map<int, std::vector<rs::RadixSpline<uint64_t> > > file_learned_index_data;
      std::map<int, std::vector<> file_learned_help_data;
    private:

    };

}

#endif //LSIM_LEARNED_INDEX_H

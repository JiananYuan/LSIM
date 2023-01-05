//
// Created by yjn on 22-12-26.
//

#ifndef LSIM_KVS_H
#define LSIM_KVS_H
#include <stdio.h>
#include <string>
#include <utility>

namespace mod {
    FILE *svlog;

    void init_kvs(const std::string& path);
    std::pair<long, long> kvs_write(const std::string& val);
    void kvs_read(const long offset, const long len, std::string& pkey_list_str);
    void close_kvs();
}

#endif //LSIM_KVS_H

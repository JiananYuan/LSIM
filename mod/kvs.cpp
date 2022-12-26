//
// Created by yjn on 22-12-26.
//

#include "kvs.h"

namespace mod {
    void init_kvs(const std::string& path) {
        svlog = fopen("svlog", "wb+");
    }

    std::pair<long, long> kvs_write(const std::string& val) {
        long offset = ftell(svlog);
        long len = sizeof(val);
        fwrite(&val, sizeof(val), 1, svlog);
        return std::make_pair(offset, len);
    }

    void kvs_read(const long offset, const long len, std::string& pkey_list_str) {
        fseek(svlog, offset, SEEK_SET);
        fread(&pkey_list_str, len, 1, svlog);
    }

    void close_kvs() {
        fclose(svlog);
    }
}
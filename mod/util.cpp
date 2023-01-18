//
// Created by jianan yuan on 2023/1/10.
//

#include "util.h"

namespace mod {
    uint64_t SliceToInteger(const Slice& slice) {
      const char* data = slice.data();
      size_t size = slice.size();
      uint64_t num = 0;
      bool leading_zeros = true;

      for (int i = 0; i < size; ++i) {
        int temp = data[i];
        if (leading_zeros && temp == '0') continue;
        leading_zeros = false;
        num = (num << 3) + (num << 1) + temp - 48;
      }
      return num;
    }

}
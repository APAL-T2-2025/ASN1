#pragma once 
#include <array>

namespace apal {
  struct SkipListNode {
    uint64_t key;
    struct SkipListNode** next;
  };
}
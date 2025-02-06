#pragma once
#include <vector>

namespace apal {
  struct SkipListNode {
    uint64_t key;
    std::vector<SkipListNode*> next;

    SkipListNode(uint64_t key, uint32_t level);
  };
}
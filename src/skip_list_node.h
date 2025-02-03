#pragma once
#include <vector>


namespace apal {
  template <typename T>
  struct SkipListNode {
    T key;
    std::vector<SkipListNode> next;

    SkipListNode(T key, unsigned int level);
  };
}
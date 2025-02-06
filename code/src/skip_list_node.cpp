#include "skip_list_node.h"

namespace apal {

  SkipListNode::SkipListNode(uint64_t key, const uint32_t level)
    : key(key),
    next(std::vector<SkipListNode*>(level)) {
  }
}


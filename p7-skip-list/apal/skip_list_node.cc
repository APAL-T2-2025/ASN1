#include "skip_list_node.h"

#include "skip_list.h"

namespace apal {

  SkipListNode::SkipListNode(const int value, SkipListNode* next, SkipListNode* up, SkipListNode* down)
  : value(value),
    next(next),
    up(up),
    down(down) {};

} //namespace apal
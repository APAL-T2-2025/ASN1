#include "skip_list_node.h"

namespace apal {

  template <typename T>
  SkipListNode<T>::SkipListNode(T key, unsigned int level)
    : key(key),
    level(level + 1)
  {}
}


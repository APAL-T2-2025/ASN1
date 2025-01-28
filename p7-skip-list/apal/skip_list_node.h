#ifndef SKIP_LIST_NODE_H
#define SKIP_LIST_NODE_H

namespace apal {
  struct SkipListNode {
    int value;
    SkipListNode *next;
    SkipListNode *up;
    SkipListNode *down;

    SkipListNode(int value, SkipListNode *next, SkipListNode *up, SkipListNode *down);
  };
} // namespace apal

#endif //SKIP_LIST_NODE_H

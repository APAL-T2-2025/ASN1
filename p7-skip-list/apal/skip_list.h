#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "skip_list_node.h"

#define MAX_LEVEL 100

namespace apal {

  class SkipList {
  private:
    int size;
    SkipListNode* head;

  public:
    SkipList();
    ~SkipList();

    void insert(int key, int value);
    void remove(int key);
    int search(int key) const;
    int getSize() const;
    void print() const;
  };
} // apal

#endif //SKIP_LIST_H

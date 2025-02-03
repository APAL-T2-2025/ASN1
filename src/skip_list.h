#pragma once

#include <random>
#include "skip_list_node.h"

#define RANDOM_INT_TYPE std::uint16_t
#define LEVEL_HEIGHT_MAX sizeof(RANDOM_INT_TYPE) * CHAR_BIT
#define INF INT32_MAX
#define NEG_INF INT32_MIN


namespace apal {
  class SkipList {
  public:

    SkipList();
    ~SkipList();

    void insert(int key);
    void remove(int key);
    [[nodiscard]] int search(int key) const;
    [[nodiscard]] int get_size() const;
    void print_full() const;
    void print() const;
    void print_level(int i) const;

  private:
    inline void init_header();

    int size;
    SkipListNode* head;
    std::vector<SkipListNode*> header;

    std::mt19937_64 generator;
    std::uniform_int_distribution<uint32_t> distribution;
  };

} // apal

#endif //SKIP_LIST_H

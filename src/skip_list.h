#pragma once

#include <random>
#include <iterator>

#include "skip_list_node.h"

#define RANDOM_INT_TYPE std::uint16_t

namespace apal {

  template <typename T, typename Comparator = std::less<T>>
  class SkipList {
  public:

    explicit SkipList(unsigned int level_max, Comparator comp = Comprator());
    
    ~SkipList();

    bool insert(const T& key);
    bool remove(const T& key);
    bool contains(const T& key) const;
    [[nodiscard]] bool size() const;

    void print_full() const;

    class iterator;
    iterator begin();
    iterator end();

    class const const_iterator;
    const_iterator begin() const;
    const_iterator end() const;

  private:

    const unsigned int max_level;
    unsigned int count;
    SkipListNode<T>* head;

    Compare comp;

    std::mt19937_64 generator;
    std::uniform_int_distribution<uint32_t> distribution;

    inline unsigned int random_level();
  };

} // apal


#pragma once

#include <random>
#include <iterator>
#include <type_traits>

#include "skip_list_node.h"

#define RANDOM_INT_TYPE std::uint16_t

namespace apal {

  class SkipList {
  public:

    SkipList(uint32_t level_max = 20);
    
    ~SkipList();

    bool insert(uint64_t key);
    bool remove(uint64_t key);
    bool contains(uint64_t key) const;
    void clear();
    [[nodiscard]] size_t size() const;

    void print_full() const;

//     class iterator;
//     iterator begin();
//     iterator end();
// 
//     class const const_iterator;
//     const_iterator begin() const;
//     const_iterator end() const;

  private:

    uint32_t  m_level_max;
    uint32_t m_level;
    size_t m_size;

    SkipListNode* m_head;
    SkipListNode* m_null;

    std::mt19937 m_generator;
    std::uniform_int_distribution<uint32_t> m_distribution;

    inline unsigned int random_level();
  };

} // apal


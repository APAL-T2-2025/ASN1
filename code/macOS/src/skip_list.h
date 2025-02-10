#pragma once

#include <random>
#include <iterator>
#include <type_traits>
#include <cstring>        
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <cassert>

#include "skip_list_node.h"

#define DEFAULT_MAX_LEVEL 32

namespace apal {

  template<int ML = DEFAULT_MAX_LEVEL>
  class SkipList {
  public:
    SkipList();
    ~SkipList();

    bool insert(uint64_t key);
    bool remove(uint64_t key);
    bool contains(uint64_t key) const;
    [[nodiscard]] size_t size() const;

    void print_full() const;

  private:
    SkipListNode* create_node(int level, const uint64_t new_key);
    void destroy_node(SkipListNode* node);

    int level;
    uint8_t m_level;
    size_t m_size;

    SkipListNode* m_head;
    SkipListNode* m_null; 

    std::mt19937 m_generator;
    std::uniform_int_distribution<uint32_t> m_distribution;

    inline unsigned int random_level();
  };


  template<int ML>
  SkipList<ML>::SkipList()
    : m_head(nullptr),
      m_level(0),
      m_size(0),
      level(0),
      m_null(nullptr)
  {
    m_distribution = std::uniform_int_distribution<uint32_t>(0, UINT32_MAX);
#ifdef DEBUG_STATIC_SEED
    m_generator.seed(DEBUG_STATIC_SEED);
#else
    m_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
#endif

    m_head = create_node(ML, uint64_t());
  }

  template<int ML>
  SkipList<ML>::~SkipList() {
    while (m_head) {
      SkipListNode* to_destroy = m_head;
      m_head = m_head->next[0];
      destroy_node(to_destroy);
    }
  }

  template<int ML>
  bool SkipList<ML>::contains(uint64_t key) const {
    const SkipListNode* node = m_head;
    for (int i = level; i >= 0; --i) {
      while (node->next[i] && node->next[i]->key < key)
        node = node->next[i];
    }
    node = node->next[0];
    return node && node->key == key;
  }

  template<int ML>
  bool SkipList<ML>::insert(uint64_t key) {
    auto node = m_head;
    SkipListNode* update[ML + 1];
    memset(update, 0, sizeof(SkipListNode*) * (ML + 1));

    // search and store references for new node.
    for (int i = level; i >= 0; i--) {
      while (node->next[i] && node->next[i]->key < key) {
        node = node->next[i];
      }
      update[i] = node;
    }
    node = node->next[0];

    // check unique
    if (node != nullptr && node->key == key) {
      return false;
    }

    auto new_level = random_level();

    // new levels, no neighbors to possibly skip to, point to head
    if (new_level > level) {
      for (int i = level + 1; i <= new_level; i++) {
        update[i] = m_head;
      }
      level = new_level;
    }
    node = create_node(new_level, key);

    // stitch the new node into the structure
    for (int i = 0; i <= new_level; i++) {
      node->next[i] = update[i]->next[i];
      update[i]->next[i] = node;
    }

    m_size++;
    return true;
  }

  template<int ML>
  bool SkipList<ML>::remove(uint64_t key) {
    SkipListNode* node = m_head;
    SkipListNode* update[ML + 1];
    memset(update, 0, sizeof(SkipListNode*) * (ML + 1));

    for (int i = level; i >= 0; i--) {
      while (node->next[i] && node->next[i]->key < key)
        node = node->next[i];
      update[i] = node;
    }
    node = node->next[0];

    if (node && node->key == key) {
      for (int i = 0; i <= level; i++) {
        if (update[i]->next[i] != node)
          break;
        update[i]->next[i] = node->next[i];
      }
      destroy_node(node);
      while (level > 0 && !m_head->next[level])
        --level;
      return true;
    }
    return false;
  }

  template<int ML>
  size_t SkipList<ML>::size() const {
    return m_size;
  }

  template<int ML>
  void SkipList<ML>::print_full() const {
    // omitted
  }

  template<int ML>
  SkipListNode* SkipList<ML>::create_node(int level, const uint64_t new_key) {
    void* node_mem = malloc(sizeof(SkipListNode));
    SkipListNode* new_node = static_cast<SkipListNode*>(node_mem);
    new (&new_node->key) uint64_t(new_key);

    void* next_mem = calloc(level + 1, sizeof(SkipListNode*));
    new_node->next = static_cast<SkipListNode**>(next_mem);
    return new_node;
  }

  template<int ML>
  void SkipList<ML>::destroy_node(SkipListNode* node) {
    free(node->next);
    free(node);
  }

  template<int ML>
  inline unsigned int SkipList<ML>::random_level() {
    auto r = m_distribution(m_generator);

    return __builtin_clz (r) % ML;
  }

} 
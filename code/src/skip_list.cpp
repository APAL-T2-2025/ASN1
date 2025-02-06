#include <bits.h>
#include <stdint.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <tuple>

#include "skip_list.h"

// #define DEBUG_STATIC_SEED 27

namespace apal {

  SkipList::SkipList(uint32_t level_max)
    : m_size(0),
    m_level(0),
    m_level_max(level_max) {

    m_distribution = std::uniform_int_distribution<uint32_t>(0, UINT32_MAX);

#ifdef DEBUG_STATIC_SEED
    m_generator.seed(DEBUG_STATIC_SEED);
#else
    m_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
#endif

    m_head = new SkipListNode(uint64_t(), m_level_max);
    m_null = m_head;
    m_head->next.assign(m_level_max, m_null);
  }

  SkipList::~SkipList() {
//     clear();
    delete m_head;
  }

  bool SkipList::contains(uint64_t key) const {
    return false;
  }
  
  bool SkipList::insert(uint64_t key) {
    auto node_curr = m_head;
    auto new_node_next = std::vector<SkipListNode*>(m_level_max);

    // start from the top of the head, move down if it points to null
    // get all next references for new node
    for (int i = 0; i <= m_level; i++) {
      int idx = m_level - i;
      while (node_curr->next[idx] != m_null && node_curr->next[idx]->key < key) {
        node_curr = node_curr->next[idx];
      }
      new_node_next[idx] = node_curr;
    }

    // check unique
    node_curr = node_curr->next[0];
    if (node_curr != m_null && node_curr->key == key) {
      return false;
    }

    // new levels, no neighbors to possibly skip to, point to null
    auto new_level = random_level();

    // auto new_level = 0;
    if (new_level > m_level) {
      for (auto i = m_level; i <= new_level; i++) {
        new_node_next[i] = m_null;
      }
      m_level = new_level;
    }

    // stitch the new_node_next at the insertion point with the new node
    node_curr = new SkipListNode(key, new_level+1);
    for (auto i = 0; i <= new_level; i++) {
      node_curr->next[i] = new_node_next[i]->next[i];
      new_node_next[i]->next[i] = node_curr;
    }

    m_size++;
    return true;
  }

  bool SkipList::remove(uint64_t key) {
    return false;
  }

  void SkipList::clear() {

    SkipListNode* node = m_head->next[0];

    while (node) {
      SkipListNode* next = node->next[0];
      delete node;
      node = next;
    }

    for (int i = 0; i <= m_level_max; i++) {
      m_head->next[i] = nullptr;
    }

    m_level = 0;
    m_size = 0;
  }

  size_t SkipList::size() const
  {
    return m_size;
  }

  void SkipList::print_full() const {
    if (m_size == 0) {
      return;
    }

    std::vector<std::tuple<int, size_t>> key_level;
    auto node_curr = m_head->next[0];

    for (auto node_curr = m_head->next[0]; node_curr != m_null; ) {
      key_level.emplace_back(node_curr->key, node_curr->next.size()-1);
      node_curr = node_curr->next[0];
    }

    int padding = 6;

    for (int i = m_level; i >= 0; i--) {
      std::cout << std::setw(padding) << 'h';
      std::cout << " | ";

      for (int j = 0; j < m_size; j++) {

        auto key = std::get<0>(key_level[j]);
        auto level = std::get<1>(key_level[j]);

        if (i <= level) {
          std::cout << std::setw(padding) << key;
        }
        else {
          std::cout << std::setw(padding) << ' ';
        }
      }
      std::cout << '\n';
    }
  }

  inline unsigned int SkipList::random_level() {
    auto rand = m_distribution(m_generator);
    
    std::cout << "num: " << rand << "\n";
    uint32_t level = __lzcnt(rand);
    
    std::cout << "level: " << level << "\n";

    return level > m_level_max-1 ? m_level_max-1 : level;
  }

}  // namespace apal
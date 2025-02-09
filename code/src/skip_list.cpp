#include <bits.h>
#include <stdint.h>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <tuple>
#include <cassert>

#include "skip_list.h"

// #define DEBUG_STATIC_SEED 27

static const int max_level = 32;

namespace apal {

  SkipList::SkipList()
    : m_head(nullptr), m_level(0) {

    m_distribution = std::uniform_int_distribution<uint32_t>(0, UINT32_MAX);
#ifdef DEBUG_STATIC_SEED
    m_generator.seed(DEBUG_STATIC_SEED);
#else
    m_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
#endif

    m_head = create_node(max_level, uint64_t());
  }

  SkipList::~SkipList() {
    while (m_head) {
      SkipListNode* to_destroy = m_head;
      m_head = m_head->next[0];
      destroy_node(to_destroy);
    }
  }

  bool SkipList::contains(uint64_t key) const {
    
    const SkipListNode* node = m_head;
    for (int i = level; i >= 0; --i) {
      while (node->next[i] && node->next[i]->key < key)
        node = node->next[i];
    }

    node = node->next[0];
    return node && node->key== key;
  }
  
  bool SkipList::insert(uint64_t key) {

    auto node = m_head;
    SkipListNode* update[max_level + 1];
    memset(update, 0, sizeof(SkipListNode*) * (max_level + 1));

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

  bool SkipList::remove(uint64_t key) {
      SkipListNode* node = m_head;
      SkipListNode* update[max_level + 1];
      memset(update, 0, sizeof(SkipListNode*) * (max_level + 1));

      for (int i = level; i >= 0; i--)
      {
        while (node->next[i] && node->next[i]->key < key)
          node = node->next[i];
        update[i] = node;
      }
      node = node->next[0];

      if (node->key == key)
      {
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

  size_t SkipList::size() const
  {
    return m_size;
  }

  void SkipList::print_full() const {
    /* if (m_size == 0) {
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
     }*/
  }

  apal::SkipListNode* SkipList::create_node(int level, const uint64_t new_key)
  {
    void* node_mem = malloc(sizeof(SkipListNode));
    SkipListNode* new_node = static_cast<SkipListNode*>(node_mem);
    new (&new_node->key) uint64_t(new_key);

    void* next_mem = calloc(level + 1, sizeof(SkipListNode*));
    new_node->next = static_cast<SkipListNode**>(next_mem);
    return new_node;
  }

  void SkipList::destroy_node(SkipListNode* node)
  {
    free(node->next);
    free(node);
  }

  inline unsigned int SkipList::random_level() {
    auto rand = m_distribution(m_generator);
    
    return __lzcnt(rand);
  }

}  // namespace apal
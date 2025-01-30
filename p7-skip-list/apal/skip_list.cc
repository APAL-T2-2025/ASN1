#include "skip_list.h"

#include <bits/chrono.h>
#include <iostream>
#include <random>
#include <bits.h>
#include <stdint.h>

#define LEVEL_HEIGHT_MAX 8
#define RANDOM_INT_SIZE_MAX UINT8_MAX

namespace apal {

  SkipList::Node::Node(const int key, const int level, Node* next, Node* up,
                     Node* down)
    : key(key), level(level), next(next), up(up), down(down) {}


  SkipList::SkipList()
  : size(0), distribution(0, RANDOM_INT_SIZE_MAX) {
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    init_header();
  }


  SkipList::~SkipList() {}

  void SkipList::init_header() {
    header = std::vector<Node*>(LEVEL_HEIGHT_MAX);
    auto curr = new Node(-INT_MAX, 0, nullptr, nullptr, nullptr);
    header[curr->level] = curr;

    while (curr->level < LEVEL_HEIGHT_MAX-1) {
      curr->up = new Node(-INT_MAX, curr->level + 1, nullptr, nullptr, curr);
      curr = curr->up;
      header[curr->level] = curr;
    }

    head = header[LEVEL_HEIGHT_MAX-1];
  }


  void SkipList::insert(const int key) {

    const u_int64 tosses = distribution(generator);
    u_int64 levels = std::countr_one(tosses); // coin tosses

    // search
    Node* cursor_curr = head;
    Node* cursor_prev = cursor_curr;

    while (true) {

      bool is_end = (cursor_curr->down == nullptr && cursor_curr->next == nullptr);

      // insertion point found
      if (cursor_curr->key >= key || is_end) {
        cursor_curr = cursor_prev;
        break;
      }

      // end of level
      if (cursor_curr->next == nullptr) {
        cursor_curr = cursor_curr->down;
        continue;
      }

      if (cursor_curr->next->key > key) {
        cursor_curr = cursor_curr->down;
      }
      else {
        cursor_curr = cursor_curr->next;
      }

      cursor_prev = cursor_curr;
    }

    // go to level 0
    while (cursor_curr->down != nullptr) {
      cursor_curr = cursor_curr->down;
    }

    // insert, from head, promote inserted node from level 0
    cursor_curr->next = new Node(key, 0, cursor_curr->next, nullptr, nullptr);
    Node* inserted_node = cursor_curr->next;

    for (int i = 1; i < levels; i++) {
      cursor_curr = header[i];

      while (cursor_curr->next != nullptr) {
        if (cursor_curr->key >= key) {
          cursor_curr = cursor_prev;
          break;
        }
        cursor_curr = cursor_curr->next;
      }

      cursor_curr->next = new Node(key, i, cursor_curr->next, nullptr, inserted_node);
      inserted_node->up = cursor_curr->next;
      inserted_node = cursor_curr->next;
    }

    size++;
  }


  void SkipList::remove(int key) {}

  int SkipList::search(int key) const { return -1; }

  int SkipList::get_size() const { return this->size; }

  void SkipList::print() const {
    if (header[0]->next == nullptr) {
      return;
    }

    std::vector<std::tuple<int, int>> data;

    int max_level = 0;
    auto level_0_curr = header[0]->next;

    for (int i = 0; i < size; i++) {
      auto curr = level_0_curr;

      while (curr->up != nullptr) {
        curr = curr->up;
      }
      data.push_back(std::make_tuple(curr->key, curr->level));
      max_level = std::max(max_level, curr->level);
      level_0_curr = level_0_curr->next;
    }

    for (int i = max_level; i >= 0; i--) {
      std::cout << 'h' << i << " | ";
      for (int j = 0; j < size; j++) {
        if (std::get<1>(data[j]) - i >= 0) {
          std::cout << std::get<0>(data[j]) << "  ";
        }
        else {
          std::cout << "   ";
        }
      }
      std::cout << '\n';
    }
  }

} // apal
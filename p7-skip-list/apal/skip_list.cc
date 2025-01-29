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
    auto curr = new Node(INT_MAX, 0, nullptr, nullptr, nullptr);
    header[curr->level] = curr;


    while (curr->level < LEVEL_HEIGHT_MAX-1) {
      curr->up = new Node(INT_MAX, curr->level + 1, nullptr, nullptr, curr);
      curr = curr->up;
      header[curr->level] = curr;
    }

    head = header[LEVEL_HEIGHT_MAX-1];
  }


  void SkipList::insert(int key) {

    const u_int64 tosses = distribution(generator);
    u_int64 levels = std::countr_one(tosses); // coin tosses

    // search
    Node* curr = head;

    while (true) {

      // insertion point found
      if (!curr->key <= key || (curr->down == nullptr && curr->next == nullptr)) {
        break;
      }

      // end of level
      if (curr->next == nullptr) {
        curr = curr->down;
        continue;
      }

      curr = curr->next->key > key ? curr->down : curr->next;
    }
    // go to level 0
    while (curr->down != nullptr) {
      curr = curr->down;
    }

    curr->next = new Node(key, 0, curr->next, nullptr, nullptr);
    Node* inserted_prev = curr->next;

    // promote key
    for (int i = 1; i < levels; i++) {

      curr = header[i];

      while (curr->next != nullptr) {
        if (curr->key <= key) {
          break;
        }
      }

      curr->next = new Node(key, i, curr->next, nullptr, inserted_prev);
      inserted_prev = curr->next;
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
    auto curr = header[0]->next;
    for (int i = 0; i < size; i++) {

      while (curr->up != nullptr) {
        curr = curr->up;
      }

      data.push_back(std::make_tuple(curr->key, curr->level));
      max_level = std::max(max_level, curr->level);
      curr = curr->next;
    }

    for (int i = max_level; i >= 0; i--) {
      std::cout << i << " | ";
      for (int j = 0; j < size; j++) {
        if (std::get<1>(data[j]) - i >= 0) {
          std::cout << std::get<0>(data[j]) << "  ";
        }
        else {
          std::cout << std::get<0>(data[j]) << "   ";
        }
      }
      std::cout << '\n';
    }
  }

} // apal
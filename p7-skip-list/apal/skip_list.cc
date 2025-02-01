#include "skip_list.h"

#include <bits/chrono.h>
#include <iostream>
#include <random>
#include <bits.h>
#include <stdint.h>
#include <iomanip>

#define STATIC_SEED 27

namespace apal {

  SkipList::Node::Node(const int key, Node* next, Node* up,
                     Node* down)
    : key(key), next(next), up(up), down(down) {}

  SkipList::SkipList()
  : size(0), distribution(0, std::numeric_limits<RANDOM_INT_TYPE>::max()) {

    // set seed
    #ifdef STATIC_SEED
    generator.seed(STATIC_SEED);
    #else
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    #endif

    // create header and initialize -INFINITE and INFINITE
    init_header();
  }

  SkipList::~SkipList() {}

  void SkipList::init_header() {
    header = std::vector<Node*>(LEVEL_HEIGHT_MAX);

    auto head_curr = new Node(NEG_INF, nullptr, nullptr, nullptr);
    head_curr->next = new Node(INF, nullptr, nullptr, nullptr);
    header[0] = head_curr;

    for (int i = 1; i < LEVEL_HEIGHT_MAX; i++) {
      head_curr->up = new Node(NEG_INF, nullptr, nullptr, head_curr);
      head_curr->up->next = new Node(INF, nullptr, nullptr, head_curr->next);
      head_curr = head_curr->up;
      header[i] = head_curr;
    }

    head = header[LEVEL_HEIGHT_MAX-1];
  }

  void SkipList::insert(const int key) {

    const RANDOM_INT_TYPE coin_tosses = distribution(generator); // acts like many tosses.
    const RANDOM_INT_TYPE levels = std::countr_zero(coin_tosses); // count the l leading contiguous 0(heads)

    // search
    Node* cursor_curr = head;

    while (true) {

      // no more on this level, go down.
      if ((cursor_curr->next == nullptr || cursor_curr->next->key == INF) && cursor_curr->down != nullptr) {
        cursor_curr = cursor_curr->down;
      }
      else if (cursor_curr->next->key > key) {
        if (cursor_curr->down != nullptr) {
          cursor_curr = cursor_curr->down;
        } else {
          break;
        }
      }
      else {
        cursor_curr = cursor_curr->next;
      }
    }

    // go to level 0
    while (cursor_curr->down != nullptr) {
      cursor_curr = cursor_curr->down;
    }

    // insert at level 0
    cursor_curr->next = new Node(key, cursor_curr->next, nullptr, nullptr);
    Node* inserted_node = cursor_curr->next;

    // promote new key to every level from header
    for (int i = 1; i < levels; i++) {

      cursor_curr = header[i];
      while (!(cursor_curr->next->key > key)) {
        cursor_curr = cursor_curr->next;
      }

      cursor_curr->next = new Node(key, cursor_curr->next, nullptr, inserted_node);
      inserted_node->up = cursor_curr->next;
      inserted_node = cursor_curr->next;
    }

    size++;
  }


  void SkipList::remove(int key) {}

  int SkipList::search(int key) const { return -1; }

  int SkipList::get_size() const { return this->size; }

  void SkipList::print_full() const {
    if (header[0]->next == nullptr) {
      return;
    }

    std::vector<std::tuple<int, int>> data;

    auto level_0_curr = header[0]->next;

    for (int i = 0; i < size; i++) {
      auto curr = level_0_curr;
      auto level = 0;
      while (curr->up != nullptr) {
        curr = curr->up;
        level++;
      }
      data.push_back(std::make_tuple(curr->key, level));
      level_0_curr = level_0_curr->next;
    }

    for (int i = LEVEL_HEIGHT_MAX; i >= 0; i--) {
      int padding = 6;
      std::cout << std::setw(padding) <<'h';
      std::cout << " | ";
      for (int j = 0; j < size; j++) {

        if (std::get<1>(data[j]) - i >= 0) {
          std::cout << std::setw(padding) <<  std::get<0>(data[j]);
        }
        else {
          std::cout << std::setw(padding) << ' ';
        }
      }
      std::cout << '\n';
    }
  }

  void SkipList::print() const {
    for (auto curr = header[0]; curr != nullptr;) {
      std::cout << curr->key << ", ";
      curr = curr->next;
    }
    std::cout << '\n';
  }

  void SkipList::print_level(const int i) const {
    for (auto curr = header[i]; curr != nullptr;) {
      std::cout << curr->key << ", ";
      curr = curr->next;
    }
    std::cout << '\n';
  }

} // apal
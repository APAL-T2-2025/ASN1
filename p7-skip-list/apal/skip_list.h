#pragma once
#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#define RANDOM_INT_TYPE std::uint16_t
#define LEVEL_HEIGHT_MAX sizeof(RANDOM_INT_TYPE) * CHAR_BIT
#define INFINITY INT16_MAX

#include <random>

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

    struct Node {
      int key;
      const int level;
      Node* next;
      Node* up;
      Node* down;

      Node(int key, int level, Node *next, Node *up, Node *down);
    };

    int size;
    Node* head;
    std::vector<Node*> header;

    std::mt19937_64 generator;
    std::uniform_int_distribution<RANDOM_INT_TYPE> distribution;
  };

} // apal

#endif //SKIP_LIST_H

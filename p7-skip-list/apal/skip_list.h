#pragma once
#ifndef SKIP_LIST_H
#define SKIP_LIST_H

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
    void print() const;

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
    std::uniform_int_distribution<std::uint8_t> distribution;
  };

} // apal

#endif //SKIP_LIST_H

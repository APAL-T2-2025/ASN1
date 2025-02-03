#include <iostream>
#include "skip_list.h"


int main() {
  apal::SkipList sl;
  sl.insert(1);
  sl.insert(2);
  sl.insert(3);

  sl.print_full();
}
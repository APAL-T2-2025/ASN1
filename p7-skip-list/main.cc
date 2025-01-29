#include <nanobench.h>

#include <atomic>

#include "apal/skip_list.h"

int main() {
  // int y = 0;
  // std::atomic<int> x(0);
  // ankerl::nanobench::Bench().run("compare_exchange_strong", [&] {
  //     x.compare_exchange_strong(y, 0);
  // });

  using namespace apal;
  auto sl = SkipList();

  sl.insert(1);
  sl.insert(2);
  sl.insert(3);
  sl.insert(4);
  sl.insert(5);
  sl.insert(6);

  sl.print();

}
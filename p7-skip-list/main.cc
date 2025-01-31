#include <nanobench.h>

#include <iostream>


#include "apal/skip_list.h"

void benchmark(bool viz);
void print_benchmark();

int main() {
  // ankerl::nanobench::Bench b;
  // b.unit("uint64_t")
  //   .warmup(100)
  //   .relative(true)
  //   .minEpochIterations(700)
  //   .doNotOptimizeAway(benchmark)
  //   .performanceCounters(true);
  //
  // b.run("Skip List Benchmark", [&] {benchmark(false);});
  // std::cout << b.complexityBigO() << std::endl;

  benchmark(true);

}

void benchmark(const bool viz) {
  using namespace apal;
  auto sl = SkipList();
  std::cout << LEVEL_HEIGHT_MAX << '\n';

  auto keys =
    {215, 43, 88, 252, 71, 89, 259, 234, 9, 4};

  for (const auto k : keys) {
    sl.insert(k);
    std::cout << '\n';
    sl.print_level(1);
    sl.print_level(0);

  }

  // if (viz) {
  //   std::cout << '\n';
  //   // sl.print();/
  //   sl.print_full();
  // }
}


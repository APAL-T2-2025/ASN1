#include <nanobench.h>

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "apal/skip_list.h"


int main() {
  ankerl::nanobench::Bench bench;
  bench.unit("op").warmup(100).minEpochIterations(11003).relative(true).performanceCounters(true);

  const std::vector<int> test_sizes = {10, 100, 1000};

  for (int n : test_sizes) {

    // Test Cases
    std::vector<int> keys(n);
    std::iota(keys.begin(), keys.end(), 0);
    std::shuffle(keys.begin(), keys.end(), std::mt19937{std::random_device{}()});


    // Benchmark insertion
    bench.batch(n).run("Insert " + std::to_string(n), [&] {
      apal::SkipList sl = apal::SkipList();
      for (int k : keys) {
          sl.insert(k);
      }
      // ankerl::nanobench::doNotOptimizeAway(sl);
    });


    // sl.print_full();
  }


}



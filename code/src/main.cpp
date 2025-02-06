#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>

#include "skip_list.h"

int main() {

  int n = 1000;

  std::ofstream fileOut("output\coin_flips.txt");
//   std::ofstream fileOut("output\count_leading_zeros.txt");

  std::cout.rdbuf(fileOut.rdbuf());


  std::vector<uint64_t> keys(n);
  std::iota(keys.begin(), keys.end(), 0);
//   std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

  auto sl = apal::SkipList();
  
  for (auto key : keys) {
    sl.insert(key);
  }
  sl.print_full();
  std::cout << '\n';


}
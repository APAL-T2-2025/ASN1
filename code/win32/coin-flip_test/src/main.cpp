//#include <iostream>
//#include <algorithm>
//#include <numeric>
//#include <fstream>
//#include <chrono>
//#include <random>
//#include "Timer.h"
//
//std::random_device rd;
//std::mt19937 gen;
//std::uniform_int_distribution<uint32_t> dist_int;
//std::uniform_real_distribution<double> dist_real;
//
//inline uint32_t coin_flip_count_leading() {
//  auto rand = dist_int(gen);
//  return __lzcnt(rand);
//}
//
//inline uint32_t coin_flip_for_real() {
//
//  auto heads = 0;
//  while ( dist_real(gen) > 0.5) {
//    heads++;
//  }
//
//  return std::min(heads, 32);
//}
//
//void test_distrib() {
//  gen = std::mt19937(rd());
//  int n = 2E6;
//
//  // TEST DISTRIBUTION
//  std::ofstream fileOut;
//
//  // count leading
//  fileOut = std::ofstream("../output/coin_flips_count_leading_dist.txt");
//  std::cout.rdbuf(fileOut.rdbuf());
//  dist_int = std::uniform_int_distribution<uint32_t>(0, UINT32_MAX);
//
//  for (int i = 0; i < n; i++)
//    std::cout << coin_flip_count_leading() << "\n";
//  fileOut.close();
//
//  // coin flip for real
//  fileOut = std::ofstream("../output/coin_flips_for_real_dist.txt");
//  std::cout.rdbuf(fileOut.rdbuf());
//  dist_real = std::uniform_real_distribution<double>(0.0, 1.0);
//
//  for (int i = 0; i < n; i++)
//    std::cout << coin_flip_for_real() << "\n";
//  fileOut.close();
//}
//
//void test_speed() {
//  gen = std::mt19937(rd());
//  int n = 1E6;
//
//  std::ofstream fileOut;
//  fileOut = std::ofstream("../output/coin_flips_speed.txt");
//  std::cout.rdbuf(fileOut.rdbuf());
//
//  // count leading
//  dist_int = std::uniform_int_distribution<uint32_t>(0, UINT32_MAX);
//  dist_real = std::uniform_real_distribution<double>(0.0, 1.0);
//
//  std::cout << "coin_flip_count_leading" << '\n';
//  {
//    Timer timer;
//    for (int i = 0; i < n; i++)
//      coin_flip_count_leading();
//  }
//  std::cout << '\n';
//
//  std::cout << "coin_flip_for_real" << '\n';
//  {
//    Timer timer;
//    for (int i = 0; i < n; i++)
//      coin_flip_for_real();
//  }
//
//  fileOut.close();
//}

//int main() {
//  // TEST SPEED
//  test_speed();
//  test_distrib();
//}
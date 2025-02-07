//#include "fc/btree.h"
//#include <iostream>
//#include <string>
//
//#include <windows.h>
//#include <psapi.h>
//
//#include <benchmark/benchmark.h>
//#include <map>
//#include <utility>
//#include <gflags/gflags.h>
//#include <numeric>
//#include <random>
//
//
//inline static size_t GetMemRam() {
//  PROCESS_MEMORY_COUNTERS memInfo;
//
//  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
//    return memInfo.WorkingSetSize / 1024; // KB
//  }
//
//  return -1;
//}
//
//inline static size_t GetMemPagefile() {
//  PROCESS_MEMORY_COUNTERS memInfo;
//  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
//    return memInfo.PagefileUsage / 1024; // KB
//  }
//  return -1;
//}
//
//template <int B>
//static void BM_MapInsertion(benchmark::State& state) {
//
//  std::vector<int> keys(state.range(0));
//  std::iota(keys.begin(), keys.end(), 0);
//  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });
//
//  state.PauseTiming();
//  double memRam = GetMemRam();
//  double memPage = GetMemPagefile();
//
//  namespace fc = frozenca;
//  fc::BTreeSet<int, B> btree;
//
//  state.ResumeTiming();
//  for (auto _ : state) {
//    for (auto key : keys) {
//      benchmark::DoNotOptimize(btree.insert(key));
//    }
//  }
//
//  state.counters["RAM"] = double(GetMemRam())- memRam ;
//  state.counters["Page"] = double(GetMemPagefile())- memPage;
//}
//
////BENCHMARK_TEMPLATE(BM_MapInsertion, 2)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 4)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 6)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 8)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 16)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 32)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 64)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 128)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 256)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 512)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 1024)->Range(1 << 10, 1 << 18);
////BENCHMARK_TEMPLATE(BM_MapInsertion, 2048)->Range(1 << 10, 1 << 18);
//
//BENCHMARK_TEMPLATE(BM_MapInsertion, 2)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 4)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 6)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 8)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 16)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 32)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 64)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 128)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 256)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 512)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 1024)->Arg(20E6);
//BENCHMARK_TEMPLATE(BM_MapInsertion, 2048)->Arg(20E6);
//
//BENCHMARK_MAIN();

//#include <iostream>
//#include <string>
//#include <windows.h>
//#include <psapi.h>
//#include <benchmark/benchmark.h>
//#include <set>
//#include <numeric>
//#include <random>
//#include "skip_list.h"
//
//inline static size_t GetMemRam() {
//  PROCESS_MEMORY_COUNTERS memInfo;
//  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
//    return memInfo.WorkingSetSize / 1024; // KB
//  }
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
//inline static int GetRandomInt(int max) {
//  std::mt19937 rng(std::random_device{}());
//  std::uniform_int_distribution<int> dist(0, max);
//  return dist(rng);
//}
//
//inline static std::vector<int> GetRandomVector(int n) {
//  std::vector<int> keys(n);
//  std::iota(keys.begin(), keys.end(), 0);
//  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });
//  return keys;
//}
//
//static void SkipList_Insertion(benchmark::State& state) {
//  int n = state.range(0);
//
//  std::vector<int> keys = GetRandomVector(n);
//  double memRam = GetMemRam(), memPage = GetMemPagefile();
//  auto sl = apal::SkipList<2>();
//
//  for (auto _ : state) {
//    for (auto key : keys) { benchmark::DoNotOptimize(sl.insert(key)); }
//  }
//
//  state.counters["RAM"] = double(GetMemRam()) - memRam;
//  state.counters["Page"] = double(GetMemPagefile()) - memPage;
//  state.SetItemsProcessed(state.iterations());
//
//}
//
//static void OrderedMap_Insertion(benchmark::State& state) {
//  int n = state.range(0);
//
//  std::vector<int> keys = GetRandomVector(n);
//  double memRam = GetMemRam(), memPage = GetMemPagefile();
//  std::set<int> ordered_set;
//
//  for (auto _ : state) {
//    state.PauseTiming();
//    for (auto key : keys) { benchmark::DoNotOptimize(ordered_set.insert(key)); }
//  }
//
//  state.counters["RAM"] = double(GetMemRam()) - memRam;
//  state.counters["Page"] = double(GetMemPagefile()) - memPage;
//  state.SetItemsProcessed(state.iterations());
//}
//
//static void SkipList_Search(benchmark::State& state) {
//  int n = state.range(0);
//
//  std::vector<int> keys = GetRandomVector(n);
//  double memRam = GetMemRam(), memPage = GetMemPagefile();
//  auto sl = apal::SkipList();
//  for (auto key : keys) { sl.insert(key); }
//
//  for (auto _ : state) {
//    for (auto key : keys) { benchmark::DoNotOptimize(sl.contains(key)); }
//  }
//
//  state.counters["RAM"] = double(GetMemRam()) - memRam;
//  state.counters["Page"] = double(GetMemPagefile()) - memPage;
//  state.SetItemsProcessed(state.iterations());
//}
//
//static void OrderedMap_Search(benchmark::State& state) {
//  int n = state.range(0);
//
//  std::vector<int> keys = GetRandomVector(n);
//  double memRam = GetMemRam(), memPage = GetMemPagefile();
//  std::set<int> ordered_set;
//  for (auto key : keys) { ordered_set.insert(key); }
//
//  for (auto _ : state) {
//    for (auto key : keys) { benchmark::DoNotOptimize(ordered_set.contains(key)); }
//  }
//
//  state.counters["RAM"] = double(GetMemRam()) - memRam;
//  state.counters["Page"] = double(GetMemPagefile()) - memPage;
//  state.SetItemsProcessed(state.iterations());
//}
//
//// New
//
////BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8, 8 << 8)->MinWarmUpTime(1)->Iterations(8 << 17);
////BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8 << 9, 8 << 16)->MinWarmUpTime(1)->Iterations(8 << 16);
////BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8 << 16, 8 << 20)->MinWarmUpTime(0)->Iterations(8);
////
////BENCHMARK(SkipList_Insertion)->RangeMultiplier(2)->Range(8, 8 << 8)->MinWarmUpTime(1)->Iterations(8 << 17);
////BENCHMARK(SkipList_Insertion)->RangeMultiplier(2)->Range(8 << 9, 8 << 16)->MinWarmUpTime(1)->Iterations(8 << 16);
////BENCHMARK(SkipList_Insertion)->RangeMultiplier(2)->Range(8 << 16, 8 << 20)->MinWarmUpTime(0)->Iterations(8);
////
////BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8, 8 << 8)->MinWarmUpTime(1)->Iterations(8 << 17);
////BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8 << 9, 8 << 16)->MinWarmUpTime(1)->Iterations(8 << 16);
////BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8 << 16, 8 << 20)->MinWarmUpTime(0)->Iterations(8);
////
////BENCHMARK(SkipList_Search)->RangeMultiplier(2)->Range(8, 8 << 8)->MinWarmUpTime(1)->Iterations(8 << 17);
////BENCHMARK(SkipList_Search)->RangeMultiplier(2)->Range(8 << 9, 8 << 16)->MinWarmUpTime(1)->Iterations(8 << 16);
////BENCHMARK(SkipList_Search)->RangeMultiplier(2)->Range(8 << 16, 8 << 20)->MinWarmUpTime(0)->Iterations(8);
//
//// Preliminary
//
//
//BENCHMARK(SkipList_Insertion)->RangeMultiplier(2)->Range(8, 8 << 8);
//BENCHMARK(SkipList_Insertion)->RangeMultiplier(2)->Range(8 << 9, 8 << 16);
//BENCHMARK(SkipList_Insertion)->RangeMultiplier(2)->Range(8 << 16, 8 << 20);
//
//BENCHMARK(SkipList_Search)->RangeMultiplier(2)->Range(8, 8 << 8);
//BENCHMARK(SkipList_Search)->RangeMultiplier(2)->Range(8 << 9, 8 << 16);
//BENCHMARK(SkipList_Search)->RangeMultiplier(2)->Range(8 << 16, 8 << 20);
//
//BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8, 8 << 8);
//BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8 << 9, 8 << 16);
//BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8 << 16, 8 << 20);
//
//BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8, 8 << 8);
//BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8 << 9, 8 << 16);
//BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8 << 16, 8 << 20);
//
//
//
//
//
//BENCHMARK_MAIN();

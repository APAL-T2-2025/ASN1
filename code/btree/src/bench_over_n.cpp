#include "fc/btree.h"
#include <iostream>
#include <string>

#include <windows.h>
#include <psapi.h>

#include <benchmark/benchmark.h>
#include <map>
#include <utility>
#include <gflags/gflags.h>
#include <numeric>
#include <random>


inline static size_t GetMemRam() {
  PROCESS_MEMORY_COUNTERS memInfo;

  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
    return memInfo.WorkingSetSize / 1024; // KB
  }

  return -1;
}

inline static size_t GetMemPagefile() {
  PROCESS_MEMORY_COUNTERS memInfo;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
    return memInfo.PagefileUsage / 1024; // KB
  }
  return -1;
}

template <int B>
static void BTreeMap_Insertion(benchmark::State& state) {

  std::vector<int> keys(state.range(0));
  std::iota(keys.begin(), keys.end(), 0);
  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

  state.PauseTiming();
  double memRam = GetMemRam();
  double memPage = GetMemPagefile();

  namespace fc = frozenca;
  fc::BTreeSet<int, B> btree;

  state.ResumeTiming();
  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(btree.insert(key));
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
}

static void OrderedMap_Insertion(benchmark::State& state) {

  state.PauseTiming();

  std::vector<int> keys(state.range(0));
  std::iota(keys.begin(), keys.end(), 0);
  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

  double memRam = GetMemRam();
  double memPage = GetMemPagefile();

  std::set<int> ordered_set;

  state.ResumeTiming();
  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(ordered_set.insert(key));
    }
  }
  state.PauseTiming();


  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
}


template <int B>
static void BTreeMap_Search(benchmark::State& state) {

  namespace fc = frozenca;
  state.PauseTiming();


  double memRam = GetMemRam();
  double memPage = GetMemPagefile();

  std::vector<int> keys(state.range(0));
  std::iota(keys.begin(), keys.end(), 0);
  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });



  fc::BTreeSet<int, B> btree;

  for (auto key : keys) {
    btree.insert(key);
  }

  state.ResumeTiming();

  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(btree.find(key));
    }
  }
  state.PauseTiming();

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
}


static void OrderedMap_Search(benchmark::State& state) {

  std::vector<int> keys(state.range(0));
  std::iota(keys.begin(), keys.end(), 0);
  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

  double memRam = GetMemRam();
  double memPage = GetMemPagefile();

  std::set<int> ordered_set;

  for (auto key : keys) {
    ordered_set.insert(key);
  }

  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(ordered_set.find(key));
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
}

BENCHMARK(OrderedMap_Insertion)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Insertion, 2)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Insertion, 4)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Insertion, 5)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Insertion, 6)->RangeMultiplier(2)->Range(8, 8 << 22);

BENCHMARK(OrderedMap_Search)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Search, 2)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Search, 4)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Search, 5)->RangeMultiplier(2)->Range(8, 8 << 22);
BENCHMARK_TEMPLATE(BTreeMap_Search, 6)->RangeMultiplier(2)->Range(8, 8 << 22);

BENCHMARK_MAIN();

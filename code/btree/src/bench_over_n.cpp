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
static void BTreeMapInsertion(benchmark::State& state) {

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

  state.counters["RAM"] = double(GetMemRam())- memRam ;
  state.counters["Page"] = double(GetMemPagefile())- memPage;
}

static void OrderedMapInsertion(benchmark::State& state) {
  std::vector<int> keys(state.range(0));
  std::iota(keys.begin(), keys.end(), 0);
  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });

  state.PauseTiming();
  double memRam = GetMemRam();
  double memPage = GetMemPagefile();

  std::map<int, int> ordered_map;

  state.ResumeTiming();
  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(ordered_map.insert({ key, key }));
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
}

BENCHMARK(OrderedMapInsertion)->RangeMultiplier(2)->Range(8, 8 << 20)->Complexity();

BENCHMARK_TEMPLATE(BTreeMapInsertion, 4)->RangeMultiplier(2)->Range(8, 8 << 20)->Complexity();
BENCHMARK_TEMPLATE(BTreeMapInsertion, 5)->RangeMultiplier(2)->Range(8, 8<<20)->Complexity();
BENCHMARK_TEMPLATE(BTreeMapInsertion, 6)->RangeMultiplier(2)->Range(8, 8<<20)->Complexity();

BENCHMARK_MAIN();

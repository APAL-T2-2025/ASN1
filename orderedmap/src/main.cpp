#include <iostream>
#include <string>
#include <map>
#include <random>
#include <numeric>
#include <windows.h>
#include <psapi.h>
#include <benchmark/benchmark.h>

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

static void BM_MapInsertion(benchmark::State& state) {
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

BENCHMARK(BM_MapInsertion)->Arg(20E6);

BENCHMARK_MAIN();
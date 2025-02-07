#include "fc/btree.h"
#include <iostream>
#include <string>

#include <windows.h>
#include <psapi.h>

#include <benchmark/benchmark.h>
#include <map>
#include <utility>
#include <gflags/gflags.h>

static void CustomArgs(benchmark::internal::Benchmark* bench) {

  int param_b[] = { 2, 4, 6, 8, 16, 32, 64, 128, 256, 512, 1024 };
  int param_n[] = { 10E6, 20E6, 40E6, 80E6, 160E6 };

  for (int b : param_b) {
    for (int n : param_n) {
      bench->Args({ b, n });
    }
  }
}

inline static size_t GetMemRam() {
  PROCESS_MEMORY_COUNTERS memInfo;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
    return memInfo.QuotaPeakPagedPoolUsage; // KB
  }
  return -1;
}

inline static size_t GetMemPagefile() {
  PROCESS_MEMORY_COUNTERS memInfo;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
    return memInfo.QuotaPeakNonPagedPoolUsage; // KB
  }
  return -1;
}

static void BM_MapInsertion(benchmark::State& state) {

  int memRamBefore = GetMemRam();
  int memPageBefore = GetMemPagefile();

  namespace fc = frozenca;
  fc::BTreeSet<int> btree;

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); i++) {
      btree.insert(i);
    }
    benchmark::DoNotOptimize(btree);
  }

  int memRamAfter = GetMemRam();
  int memPageAfter = GetMemPagefile();

  int memRamUsed = memRamAfter;
  int memPageUsed = memPageAfter;

  state.counters["Memory_RAM_Used"] = memPageUsed;
  state.counters["Memory_Pagefile_Used"] = memPageUsed;
}
BENCHMARK(BM_MapInsertion)->Apply(CustomArgs);

DEFINE_string(benchmark_out, "results.json", "Output file for benchmark results");
DEFINE_string(benchmark_out_format, "json", "Format of benchmark results output");

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);

  benchmark::AddCustomContext("Memory_Unit", "KB");

  return benchmark::RunSpecifiedBenchmarks();

  //std::cout << GetMemPagefile() << std::endl;
  //std::cout << GetMemRam() << std::endl;


  //std::vector<int> map;


  //for (int i = 0; i < 10000; i++)
  //  map.push_back(i);

  //std::cout << GetMemPagefile() << std::endl;
  //std::cout << GetMemRam() << std::endl;  

}

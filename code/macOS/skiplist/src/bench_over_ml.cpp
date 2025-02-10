#include <iostream>
#include <string>
#include <mach/mach.h>
#include <benchmark/benchmark.h>
#include <set>
#include <numeric>
#include <random>
#include "skip_list.h"

inline static size_t GetMemRam() {
  task_basic_info_data_t info;
  mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
  if (task_info(reinterpret_cast<task_name_t>(mach_task_self()),
                TASK_BASIC_INFO,
                reinterpret_cast<task_info_t>(&info),
                &infoCount) == KERN_SUCCESS) {
    return info.resident_size / 1024; // KB
  }
  return static_cast<size_t>(-1);
}

inline static size_t GetMemPagefile() {
  task_vm_info_data_t vmInfo;
  mach_msg_type_number_t vmInfoCount = TASK_VM_INFO_COUNT;
  if (task_info(reinterpret_cast<task_name_t>(mach_task_self()),
                TASK_VM_INFO,
                reinterpret_cast<task_info_t>(&vmInfo),
                &vmInfoCount) == KERN_SUCCESS) {
    return vmInfo.virtual_size / 1024; // KB
  }
  return static_cast<size_t>(-1);
}


inline static int GetRandomInt(int max) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, max);
  return dist(rng);
}

inline static std::vector<int> GetRandomVector(int n) {
  std::vector<int> keys(n);
  std::iota(keys.begin(), keys.end(), 0);
  std::shuffle(keys.begin(), keys.end(), std::mt19937{ std::random_device{}() });
  return keys;
}

template <int L>
static void SkipList_Insertion(benchmark::State& state) {
  int n = state.range(0);
  std::vector<int> keys = GetRandomVector(n);
  double memRam = GetMemRam(), memPage = GetMemPagefile();
  auto sl = apal::SkipList<L>();

  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(sl.insert(key));
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
  state.SetItemsProcessed(state.iterations());
}

static void OrderedMap_Insertion(benchmark::State& state) {
  int n = state.range(0);
  std::vector<int> keys = GetRandomVector(n);
  double memRam = GetMemRam(), memPage = GetMemPagefile();
  std::set<int> ordered_set;

  for (auto _ : state) {
    state.PauseTiming();
    for (auto key : keys) {
      benchmark::DoNotOptimize(ordered_set.insert(key));
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
  state.SetItemsProcessed(state.iterations());
}

template <int L>
static void SkipList_Search(benchmark::State& state) {
  int n = state.range(0);
  std::vector<int> keys = GetRandomVector(n);
  double memRam = GetMemRam(), memPage = GetMemPagefile();
  auto sl = apal::SkipList<L>();
  for (auto key : keys) { sl.insert(key); }

  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(sl.contains(key));
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
  state.SetItemsProcessed(state.iterations());
}

static void OrderedMap_Search(benchmark::State& state) {
  int n = state.range(0);
  std::vector<int> keys = GetRandomVector(n);
  double memRam = GetMemRam(), memPage = GetMemPagefile();
  std::set<int> ordered_set;
  for (auto key : keys) { ordered_set.insert(key); }

  for (auto _ : state) {
    for (auto key : keys) {
      benchmark::DoNotOptimize(ordered_set.find(key) != ordered_set.end());
    }
  }

  state.counters["RAM"] = double(GetMemRam()) - memRam;
  state.counters["Page"] = double(GetMemPagefile()) - memPage;
  state.SetItemsProcessed(state.iterations());
}

BENCHMARK_TEMPLATE(SkipList_Insertion, 2)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 4)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 6)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 8)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 10)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 12)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 14)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 16)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 18)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 22)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 24)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 26)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 28)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 30)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Insertion, 32)->Arg(8 << 14);

BENCHMARK_TEMPLATE(SkipList_Search, 2)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 4)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 6)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 8)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 10)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 12)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 14)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 16)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 18)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 22)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 24)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 26)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 28)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 30)->Arg(8 << 14);
BENCHMARK_TEMPLATE(SkipList_Search, 32)->Arg(8 << 14);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 2);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 2);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 2);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 2);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 4);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 4);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 4);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 4);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 6);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 6);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 6);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 6);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 8);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 8);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 8);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 8);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 10);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 10);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 10);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 10);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 12);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 12);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 12);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 12);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 14);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 14);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 14);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 14);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 16);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 16);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 16);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 16);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 18);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 18);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 18);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 18);

// BENCHMARK_TEMPLATE(SkipList_Insertion, 20)->Arg(8 << 20);
// BENCHMARK_TEMPLATE(SkipList_Search, 20)->Arg(8 << 20);
// BENCHMARK(OrderedMap_Insertion)->Arg(8 << 20);
// BENCHMARK(OrderedMap_Search)->Arg(8 << 20);

BENCHMARK_MAIN();

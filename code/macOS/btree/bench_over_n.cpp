#include "fc/btree.h"
#include <iostream>
#include <string>
#include <benchmark/benchmark.h>
#include <map>
#include <utility>
#include <numeric>
#include <random>
#include <mach/mach.h>
#include <Kernel/mach/task_info.h>

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

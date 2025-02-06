#include <random>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>

#include <benchmark/benchmark.h>
#include <tlx/container/btree.hpp> 

template <size_t B>
struct MyBTreeTraits : public tlx::btree_default_traits<int, int> {
  static const size_t leaf_slotmax = B;
  static const size_t inner_slotmax = B * 2;
};

struct SelectFirst {
  int operator()(const std::pair<int, int>& value) const {
    return value.first;
  }
};

template <size_t B>
static void BM_BTreeInsert(benchmark::State& state) {
  tlx::BTree<
    int,
    int,
    SelectFirst<std::pair<int, int>>, 
    std::less<int>,                  
    MyBTreeTraits<B>                 
  > btree;

  std::vector<int> data(state.range(0));
  std::iota(data.begin(), data.end(), 0);
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(data.begin(), data.end(), g);

  for (auto _ : state) {
    for (int key : data) {
      btree.insert(std::make_pair(key, key));
    }
  }
  state.SetItemsProcessed(state.range(0));
}

#define REGISTER_BENCHMARK(B) \
    BENCHMARK_TEMPLATE(BM_BTreeInsert, B)->Arg(100000);

REGISTER_BENCHMARK(16);
REGISTER_BENCHMARK(32);
REGISTER_BENCHMARK(64);
REGISTER_BENCHMARK(128);

BENCHMARK_MAIN();
#include <benchmark/benchmark.h>
#include <random>
#include <limits>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<uint32_t> dist_int(0, UINT32_MAX);
std::uniform_real_distribution<double> dist_real(0.0, 1.0);

inline uint32_t coin_flip_count_leading() {
  auto rand = dist_int(gen);
  return __builtin_clz(rand);
}

inline uint32_t coin_flip_for_real() {
  auto heads = 0;
  while (dist_real(gen) > 0.5) {
    heads++;
  }
  return std::min(heads, 32);
}

// Benchmark for count leading zeros method
static void BM_CoinFlipCountLeading(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(coin_flip_count_leading());
  }
}

// Benchmark for real coin flip method
static void BM_CoinFlipForReal(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(coin_flip_for_real());
  }
}

// Register benchmarks
BENCHMARK(BM_CoinFlipCountLeading);
BENCHMARK(BM_CoinFlipForReal);

BENCHMARK_MAIN();

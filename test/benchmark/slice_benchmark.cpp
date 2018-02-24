#if defined(GO_BENCHMARK)
#if defined(GO_BENCHMARK_SLICE) || defined(GO_BENCHMARK_ALL)
#include <benchmark/benchmark.h>
#include <go/slice.hpp>

static void c_array_call(int *data, std::size_t size) { data[0]++; }
static void BM_c_array(benchmark::State &state) {
    int buf[1024];
    for (auto _ : state) {
        c_array_call(buf, 1024);
        benchmark::DoNotOptimize(buf);
    }
}
BENCHMARK(BM_c_array);

static void slice_call(go::slice<int> slice) { slice[0]++; }
static void BM_slice(benchmark::State &state) {
    auto slice = go::slice<int>{1024};
    for (auto _ : state) {
        slice_call(slice);
        benchmark::DoNotOptimize(slice);
    }
}
BENCHMARK(BM_slice);

static void slice_ref_call(go::slice<int> &slice) { slice[0]++; }
static void BM_slice_ref(benchmark::State &state) {
    auto slice = go::slice<int>{1024};
    for (auto _ : state) {
        slice_ref_call(slice);
        benchmark::DoNotOptimize(slice);
    }
}
BENCHMARK(BM_slice_ref);

#endif // GO_BENCHMARK_MEMCPY
#endif
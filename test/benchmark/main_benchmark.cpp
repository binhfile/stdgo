/**
 * @author binhfile
 * @brief Main function for benchmark
 */
#if defined(GO_BENCHMARK) && defined(GO_BENCHMARK_ALL)
#include <benchmark/benchmark.h>
BENCHMARK_MAIN();
#endif // GO_BENCHMARK
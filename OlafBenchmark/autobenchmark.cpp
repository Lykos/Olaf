#include "autobenchmark.h"

#include <algorithm>
#include <string>
#include <QTest>

using namespace std;

namespace olaf
{
namespace benchmark
{

namespace auto_benchmark {

BenchmarkList& benchmark_list()
{
  static BenchmarkList list;
  return list;
}

bool find_benchmark(Benchmark* const benchmark)
{
  BenchmarkList& list = benchmark_list();
  if (find(list.begin(), list.end(), benchmark) != list.end()) {
    return true;
  }
  for (Benchmark* const benchmark2 : list) {
    if (benchmark2->objectName() == benchmark->objectName()) {
      return true;
    }
  }
  return false;
}

void add_benchmark(Benchmark* const benchmark)
{
  BenchmarkList& list = benchmark_list();
  if (!find_benchmark(benchmark)) {
    list.push_back(benchmark);
  }
}

GlobalResult run(const int argc, char* argv[], const string& description)
{
  GlobalResult global_result(description);
  for (Benchmark* const test : benchmark_list()) {
    QTest::qExec(test, argc, argv);
    global_result.add_sub_result(test->accumulate_results());
  }
  return global_result;
}


} // namespace benchmark
} // namespace olaf
} // namespace auto_benchmark

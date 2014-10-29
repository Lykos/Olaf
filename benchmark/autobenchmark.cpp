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

void add_benchmark(Benchmark* const benchmark)
{
  BenchmarkList& list = benchmark_list();
  list.push_back(benchmark);
}

GlobalResult run(const int argc, char* argv[], const string& description)
{
  GlobalResult global_result(description);
  for (Benchmark* const test : benchmark_list()) {
    QTest::qExec(test, argc, argv);
    global_result.add_sub_result(test->results());
  }
  return global_result;
}


} // namespace benchmark
} // namespace olaf
} // namespace auto_benchmark

#include "autobenchmark.h"

#include <algorithm>
#include <string>
#include <QTest>

using namespace std;

namespace auto_benchmark {

TestList& test_list()
{
  static TestList list;
  return list;
}

bool find_benchmark(Benchmark* const benchmark)
{
  TestList& list = test_list();
  if (find(list.begin(), list.end(), benchmark) != list.end()) {
    return true;
  }
  for (Benchmark* const test : list) {
    if (test->objectName() == benchmark->objectName()) {
      return true;
    }
  }
  return false;
}

void add_test(Benchmark* const benchmark)
{
  TestList& list = test_list();
  if (!find_benchmark(benchmark)) {
    list.push_back(benchmark);
  }
}

GlobalResult run(const int argc, char* argv[], const string& description)
{
  GlobalResult global_result(description);

  for (Benchmark* const test : test_list()) {
    QTest::qExec(test, argc, argv);
    global_result.add_sub_result(test->accumulate_results());
  }

  return global_result;
}

} // namespace auto_benchmark

#ifndef AUTOBENCHMARK_H
#define AUTOBENCHMARK_H

#include <vector>
#include <string>
#include <memory>
#include "benchmark.h"

namespace auto_benchmark {

typedef std::vector<Benchmark*> TestList;

TestList& test_list();

bool find_benchmark(Benchmark* benchmark);

void add_test(Benchmark* benchmark);

typedef CompositePerformanceResult<BenchmarkResult> ClassResult;
typedef CompositePerformanceResult<ClassResult> GlobalResult;

GlobalResult run(int argc, char* argv[], const std::string& description);

template <class T>
class Test
{
public:
  std::unique_ptr<T> child;

  Test(const char* const name) : child(new T)
  {
    child->setObjectName(name);
    auto_benchmark::add_test(child.get());
  }
};

} // namespace auto_benchmark

#define DECLARE_BENCHMARK(className) static ::auto_benchmark::Test<className> t(#className);

#endif // AUTOBENCHMARK_H

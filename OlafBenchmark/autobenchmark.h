#ifndef AUTOBENCHMARK_H
#define AUTOBENCHMARK_H

#include <vector>
#include <string>
#include <memory>
#include "benchmark.h"

namespace auto_benchmark
{

typedef std::vector<Benchmark*> BenchmarkList;

BenchmarkList& benchmark_list();

bool find_benchmark(Benchmark* benchmark);

void add_benchmark(Benchmark* benchmark);

typedef CompositeBenchmarkResult<BenchmarkResult> ClassResult;
typedef CompositeBenchmarkResult<ClassResult> GlobalResult;

GlobalResult run(int argc, char* argv[], const std::string& description);

template <class T>
class BenchmarkHolder
{
public:
  std::unique_ptr<T> child;

  BenchmarkHolder(const char* const name) : child(new T)
  {
    child->setObjectName(name);
    auto_benchmark::add_benchmark(child.get());
  }
};

} // namespace auto_benchmark

#define DECLARE_BENCHMARK(className) static ::auto_benchmark::BenchmarkHolder<className> t(#className);

#endif // AUTOBENCHMARK_H

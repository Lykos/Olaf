#include "benchmark.h"

#include <chrono>
#include <string>
#include <sstream>
#include <QtTest/QTest>
#include <iostream>

using namespace std;
using namespace chrono;

namespace olaf
{
namespace benchmark
{

Benchmark::Benchmark(const std::string& name):
  m_results(name)
{}

Benchmark::~Benchmark()
{}

CompositeBenchmarkResult<BenchmarkResult> Benchmark::results() const
{
  return m_results;
}

string Benchmark::current_test_id() const
{
  ostringstream oss;
  oss << QTest::currentTestFunction()
      << "(" << QTest::currentDataTag() << ")";
  return oss.str();
}

void Benchmark::push_result(const BenchmarkResult& result)
{
  m_results.add_sub_result(result);
}

void Benchmark::push_score(const long score)
{
  push_result(BenchmarkResult(current_test_id(), score));
}

void Benchmark::config(const Config* const config)
{
  m_config = config;
}

const Config* Benchmark::config() const
{
  return m_config;
}

Benchmark::PerformanceMeasurer::PerformanceMeasurer(Benchmark* const benchmark):
  m_benchmark(benchmark),
  m_done(false)
{
  m_timer.start();
}

bool Benchmark::PerformanceMeasurer::done() const
{
  return m_done;
}

void Benchmark::PerformanceMeasurer::next()
{
  m_benchmark->push_result(BenchmarkResult(m_benchmark->current_test_id(),
                                           milliseconds(m_timer.elapsed())));
  m_done = true;
}

} // namespace benchmark
} // namespace olaf

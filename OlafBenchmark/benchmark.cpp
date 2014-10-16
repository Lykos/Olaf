#include "benchmark.h"

#include <chrono>
#include <string>
#include <sstream>
#include <QtTest/QTest>
#include <iostream>

using namespace std;
using namespace chrono;

static const int c_iterations = 10;
static const int c_used_measurements = 2;

CompositeBenchmarkResult<BenchmarkResult> Benchmark::accumulate_results() const
{
  CompositeBenchmarkResult<BenchmarkResult> results(description());
  for (vector<BenchmarkResult>::const_iterator it = m_results.begin(); it < m_results.end(); ++it) {
    const string& description = it->description();
    milliseconds millis(0);
    int iterations = 0;
    for (; it < m_results.end() && it->description() == description; ++it) {
      millis += it->millis();
      ++iterations;
    }
    results.add_sub_result(BenchmarkResult(
                             description,
                             millis / iterations));
  }
  return results;
}

void Benchmark::push_result(const BenchmarkResult& result)
{
  m_results.push_back(result);
}

std::string Benchmark::description() const
{
  return objectName().toStdString();
}

Benchmark::PerformanceMeasurer::PerformanceMeasurer(Benchmark* const benchmark):
  m_benchmark(benchmark),
  m_iterations(0)
{
  m_timer.start();
}

Benchmark::PerformanceMeasurer::~PerformanceMeasurer()
{
  for (int i = 0; i < c_used_measurements; ++i) {
    m_benchmark->push_result(m_measurements.top());
    m_measurements.pop();
  }
}

bool Benchmark::PerformanceMeasurer::done() const
{
  return m_iterations >= c_iterations;
}

void Benchmark::PerformanceMeasurer::next()
{
  ostringstream oss;
  oss << QTest::currentTestFunction() << "(" << QTest::currentDataTag() << ")";
  m_measurements.push(BenchmarkResult(oss.str(), std::chrono::milliseconds(m_timer.elapsed())));
  ++m_iterations;
  m_timer.start();
}

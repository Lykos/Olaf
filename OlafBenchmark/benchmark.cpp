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

Benchmark::~Benchmark()
{}

CompositeBenchmarkResult<BenchmarkResult> Benchmark::accumulate_results() const
{
  CompositeBenchmarkResult<BenchmarkResult> results(objectName().toStdString());
  for (vector<BenchmarkResult>::const_iterator it = m_results.begin(); it < m_results.end(); ++it) {
    const string& description = it->description();
    if (it->has_millis()) {
      milliseconds millis(0);
      int iterations = 0;
      for (; it < m_results.end() && it->description() == description; ++it) {
        millis += it->millis();
        ++iterations;
      }
      results.add_sub_result(BenchmarkResult(
                               description,
                               millis / iterations));
    } else if (it->has_score()) {
      results.add_sub_result(BenchmarkResult(
                               description,
                               it->score()));
    }
  }
  return results;
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
  m_results.push_back(result);
}

void Benchmark::push_score(const long score)
{
  push_result(BenchmarkResult(current_test_id(), score));
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
  m_measurements.push(BenchmarkResult(m_benchmark->current_test_id(),
                                      milliseconds(m_timer.elapsed())));
  ++m_iterations;
  m_timer.start();
}

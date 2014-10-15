#include "benchmark.h"

#include <string>
#include <sstream>
#include <QtTest/QTest>
#include <iostream>

using namespace std;

static const int c_iterations = 10;
static const int c_used_measurements = 2;

CompositePerformanceResult<PerformanceResult> Benchmark::accumulate_results() const
{
  CompositePerformanceResult<PerformanceResult> results(description());
  for (vector<PerformanceResult>::const_iterator it = m_results.begin(); it < m_results.end(); ++it) {
    const string& description = it->description();
    unsigned long milliseconds = 0;
    int iterations = 0;
    for (; it < m_results.end() && it->description() == description; ++it) {
      milliseconds += it->milliseconds();
      ++iterations;
    }
    results.add_sub_result(PerformanceResult(
                             description,
                             milliseconds / static_cast<double>(iterations)));
  }
  return results;
}

void Benchmark::push_result(const PerformanceResult& result)
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
  m_measurements.push(PerformanceResult(oss.str(), m_timer.elapsed()));
  ++m_iterations;
  m_timer.start();
}

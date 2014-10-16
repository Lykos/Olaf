#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <QObject>
#include <QElapsedTimer>
#include <QtTest/QtTest>
#include <string>
#include <vector>
#include <queue>
#include "performanceresult.h"
#include "compositeperformanceresult.h"

class Benchmark : public QObject
{
  Q_OBJECT

public:
  CompositeBenchmarkResult<BenchmarkResult> accumulate_results() const;

  std::string description() const;

  void push_result(const BenchmarkResult& result);

protected:
  class PerformanceMeasurer {
  public:
    PerformanceMeasurer(Benchmark* const benchmark);
    ~PerformanceMeasurer();
    bool done() const;
    void next();
  private:
    Benchmark* const m_benchmark;
    int m_iterations;
    QElapsedTimer m_timer;
    std::priority_queue<BenchmarkResult> m_measurements;
  };

private:
  std::vector<BenchmarkResult> m_results;
};

#define OLAF_BENCHMARK for (PerformanceMeasurer m(this); !m.done(); m.next())

#endif // BENCHMARK_H

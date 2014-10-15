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
  CompositePerformanceResult<PerformanceResult> accumulate_results() const;

  std::string description() const;

  void push_result(const PerformanceResult& result);

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
    std::priority_queue<PerformanceResult, vector<PerformanceResult>, CompareMillis> m_measurements;
  };

private:
  std::vector<PerformanceResult> m_results;
};

#define OLAF_BENCHMARK for (PerformanceMeasurer m(this); !m.done(); m.next())

#endif // BENCHMARK_H

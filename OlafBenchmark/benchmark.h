#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <QObject>
#include <QElapsedTimer>
#include <QtTest/QtTest>
#include <string>
#include <vector>
#include <queue>
#include "benchmarkresult.h"
#include "compositebenchmarkresult.h"

class Benchmark : public QObject
{
  Q_OBJECT

public:
  virtual ~Benchmark();

  CompositeBenchmarkResult<BenchmarkResult> accumulate_results() const;

  virtual std::string current_test_id() const;

  void push_result(const BenchmarkResult& result);

  void push_score(long score);

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

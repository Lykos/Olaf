#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <QObject>
#include <QElapsedTimer>
#include <QtTest/QtTest>
#include <string>
#include <vector>
#include "benchmarkresult.h"
#include "compositebenchmarkresult.h"

namespace olaf
{
namespace benchmark
{

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
    explicit PerformanceMeasurer(Benchmark* const benchmark);

    bool done() const;

    void next();

  private:
    Benchmark* const m_benchmark;

    bool m_done;

    QElapsedTimer m_timer;

    BenchmarkResult m_result;
  };

private:
  std::vector<BenchmarkResult> m_results;
};

#define OLAF_BENCHMARK for (PerformanceMeasurer m(this); !m.done(); m.next())

} // namespace benchmark
} // namespace olaf

#endif // BENCHMARK_H

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

class Config;

namespace benchmark
{

class Benchmark : public QObject
{
  Q_OBJECT

public:
  explicit Benchmark(const std::string& name);

  virtual ~Benchmark();

  CompositeBenchmarkResult<BenchmarkResult> results() const;

  virtual std::string current_test_id() const;

  void push_result(const BenchmarkResult& result);

  void push_score(long score);

  void config(const Config* config);

  const Config* config() const;

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
  CompositeBenchmarkResult<BenchmarkResult> m_results;

  const Config* m_config;
};

#define OLAF_BENCHMARK for (PerformanceMeasurer m(this); !m.done(); m.next())

} // namespace benchmark
} // namespace olaf

#endif // BENCHMARK_H

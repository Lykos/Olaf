#ifndef PERFTBENCHMARK_H
#define PERFTBENCHMARK_H

#include <QObject>
#include <QtTest/QTest>
#include "autobenchmark.h"
#include "benchmark.h"

namespace olaf
{
namespace benchmark
{

class PerftBenchmark : public Benchmark
{
  Q_OBJECT

private Q_SLOTS:
  void test_perft_data();

  void test_perft();
};

DECLARE_BENCHMARK(PerftBenchmark)

} // namespace benchmark
} // namespace olaf

#endif // PERFTBENCHMARK_H
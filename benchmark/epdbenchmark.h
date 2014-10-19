#ifndef EPDBENCHMARK_H
#define EPDBENCHMARK_H

#include <string>
#include <QtTest/QTest>

#include "benchmark.h"
#include "autobenchmark.h"
#include "olaf/searcherfactory.h"
#include "olaf/simpletimedsearcher.h"
#include "olaf/nothinkingwriter.h"

namespace olaf
{
namespace benchmark
{

class EpdBenchmark : public Benchmark
{
  Q_OBJECT
public:
  EpdBenchmark();

  virtual ~EpdBenchmark();

private:
  NoThinkingWriter m_no_thinking_writer;

  SearcherFactory m_factory;

  std::unique_ptr<SimpleTimedSearcher> m_searcher;

private Q_SLOTS:
  void initTestCase();

  void test_epd();

  void test_epd_data();
};

DECLARE_BENCHMARK(EpdBenchmark)

} // namespace benchmark
} // namespace olaf

#endif // EPDBENCHMARK_H

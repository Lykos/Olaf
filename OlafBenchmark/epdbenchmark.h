#ifndef EPDBENCHMARK_H
#define EPDBENCHMARK_H

#include <string>

#include "benchmark.h"
#include "autobenchmark.h"
#include "OlafSearching/searcherfactory.h"
#include "OlafSearching/simpletimedsearcher.h"

class EpdBenchmark : public Benchmark
{
public:
  EpdBenchmark();

private:
  SearcherFactory m_factory;

  std::unique_ptr<SimpleTimedSearcher> m_searcher;

private Q_SLOTS:
  void initTestCase();

  void test_epd();

  void test_epd_data();
};

DECLARE_BENCHMARK(EpdBenchmark)

#endif // EPDBENCHMARK_H

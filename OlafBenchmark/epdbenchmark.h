#ifndef EPDBENCHMARK_H
#define EPDBENCHMARK_H

#include <string>
#include <QtTest/QTest>

#include "benchmark.h"
#include "autobenchmark.h"
#include "OlafSearching/searcherfactory.h"
#include "OlafSearching/simpletimedsearcher.h"
#include "OlafSearching/nothinkingwriter.h"

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

// DECLARE_BENCHMARK(EpdBenchmark)

#endif // EPDBENCHMARK_H

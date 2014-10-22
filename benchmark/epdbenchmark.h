#ifndef EPDBENCHMARK_H
#define EPDBENCHMARK_H

#include <string>
#include <QtTest/QTest>

#include "benchmark.h"
#include "autobenchmark.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/search/simpletimedsearcher.h"
#include "olaf/search/nothinkingwriter.h"

namespace olaf
{
namespace benchmark
{

class EpdBenchmark : public Benchmark
{
  Q_OBJECT
public:
  explicit EpdBenchmark(const std::string& epd_file);

  virtual ~EpdBenchmark();

private:
  NoThinkingWriter m_no_thinking_writer;

  SearcherFactory m_factory;

  std::unique_ptr<SimpleTimedSearcher> m_searcher;

  const std::string m_epd_file;

private Q_SLOTS:
  void initTestCase();

  void test_epd();

  void test_epd_data();
};

} // namespace benchmark
} // namespace olaf

#endif // EPDBENCHMARK_H

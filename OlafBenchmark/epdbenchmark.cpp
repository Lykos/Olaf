#include "epdbenchmark.h"

#include <cassert>
#include <fstream>
#include <QtTest/QTest>
#include <chrono>

#include "OlafSearching/epdposition.h"
#include "testutil.h"

using namespace std;
using namespace chrono;
using namespace testing;

Q_DECLARE_METATYPE(EpdPosition)

static const milliseconds c_max_time(10);

EpdBenchmark::EpdBenchmark():
  m_factory(nullptr)
{}

void EpdBenchmark::initTestCase()
{
  m_searcher.reset(new SimpleTimedSearcher(m_factory.iterative_searcher(), c_max_time));
}

void EpdBenchmark::test_epd()
{
  QFETCH(EpdPosition, position);

  Move move;
  NoStopper stopper;
  ChessBoard board(position.board);
  OLAF_BENCHMARK {
    move = m_searcher->search_timed(&board, stopper, stopper).main_variation().back();
  }
  QASSERT_THAT(position.best_moves, Contains(IsSameMove(move)));
}

void EpdBenchmark::test_epd_data()
{
  QTest::addColumn<EpdPosition>("position");

  std::unique_ptr<EpdParser> parser = m_factory.epd_parser();
  ifstream file(epd_file());
  string line;
  while (getline(file, line)) {
    EpdPosition position;
    assert(parser->parse(line, &position));
    QTest::newRow(position.id.c_str()) << position;
  }
}

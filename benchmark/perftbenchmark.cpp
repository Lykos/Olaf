#include "perftbenchmark.h"

#include <vector>
#include <QtTest/QTest>
#include <iostream>
#include <gmock/gmock-matchers.h>

#include "olaf/search/movegenerator.h"
#include "olaf/rules/movechecker.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/rules/chessboard.h"
#include "olaf/search/perft.h"
#include "testutil.h"
#include "benchmark.h"

using namespace std;
using namespace testing;

Q_DECLARE_METATYPE(olaf::ChessBoard)
Q_DECLARE_METATYPE(vector<olaf::Perft::PerftResult>)

namespace olaf
{
namespace benchmark
{

typedef Perft::PerftResult PerftResult;

const int c_depth = 2;

PerftBenchmark::PerftBenchmark():
  Benchmark("Perft")
{}

void PerftBenchmark::test_perft_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<vector<PerftResult>>("expected_results");

  for (Perft::PerftExample example : Perft::examples()) {
    QTest::newRow(example.name.c_str()) << parse_fen(example.fen) << example.expected_results;
  }
}

void PerftBenchmark::test_perft()
{
  QFETCH(ChessBoard, board);
  QFETCH(vector<PerftResult>, expected_results);
  if (expected_results.size() <= c_depth) {
    return;
  }

  unique_ptr<Perft> perft = SearcherFactory::perft();

  // perft->debug_perft(c_depth, board);
  const PerftResult& expected_result = expected_results.at(c_depth);
  PerftResult actual_result;
  OLAF_BENCHMARK {
    actual_result = perft->perft(c_depth, board);
  }
  QASSERT_THAT(actual_result, Eq(expected_result));
}

DECLARE_BENCHMARK(PerftBenchmark)

} // namespace benchmark
} // namespace olaf

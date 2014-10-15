#include "perftbenchmark.h"

#include <vector>
#include <QtTest/QTest>
#include <iostream>
#include <gmock/gmock-matchers.h>

#include "OlafSearching/movegenerator.h"
#include "OlafSearching/movecreator.h"
#include "OlafSearching/searcherfactory.h"
#include "OlafRules/chessboard.h"
#include "OlafSearching/perft.h"
#include "OlafTest/testutil.h"
#include "benchmark.h"

using namespace std;
using namespace testing;

typedef Perft::PerftResult PerftResult;

const int c_depth = 3;

Q_DECLARE_METATYPE(ChessBoard)
Q_DECLARE_METATYPE(vector<PerftResult>)

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

  SearcherFactory factory(nullptr);
  unique_ptr<Perft> perft = factory.perft();

  // perft->debug_perft(c_depth, board);
  const PerftResult& expected_result = expected_results.at(c_depth);
  PerftResult actual_result;
  OLAF_BENCHMARK {
    actual_result = perft->perft(c_depth, board);
  }
  QASSERT_THAT(actual_result, Eq(expected_result));
}
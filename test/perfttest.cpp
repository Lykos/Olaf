#include "perfttest.h"

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

using namespace std;
using namespace testing;

namespace olaf
{
namespace test
{

typedef Perft::PerftResult PerftResult;

static const int c_depth = 1;

void PerftTest::test_perft_data()
{
  QTest::addColumn<ChessBoard>("board");
  QTest::addColumn<vector<PerftResult>>("expected_results");

  for (const Perft::PerftExample& example : Perft::examples()) {
    QTest::newRow(example.name.c_str()) << parse_fen(example.fen) << example.expected_results;
  }
}

void PerftTest::test_perft()
{
  QFETCH(ChessBoard, board);
  QFETCH(vector<PerftResult>, expected_results);
  if (expected_results.size() <= c_depth) {
    return;
  }

  NoThinkingWriter no_thinking_writer;
  unique_ptr<Config> config = test_config();
  SearcherFactory factory(&no_thinking_writer);
  unique_ptr<Perft> perft = factory.perft();

  // perft->debug_perft(c_depth, board);
  const PerftResult& expected_result = expected_results.at(c_depth);
  const PerftResult& actual_result = perft->perft(c_depth, board);
  QASSERT_THAT(actual_result, Eq(expected_result));

} // namespace test
} // namespace olaf
}

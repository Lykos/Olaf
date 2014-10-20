#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <QtTest/qtest.h>
#include <string>
#include <vector>

#include "gmock/gmock-generated-matchers.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/move.h"
#include "olaf/rules/piece.h"
#include "olaf/search/perft.h"

Q_DECLARE_METATYPE(olaf::BitBoard)
Q_DECLARE_METATYPE(olaf::ChessBoard)
Q_DECLARE_METATYPE(olaf::Position)
Q_DECLARE_METATYPE(std::vector<olaf::Perft::PerftResult>)
Q_DECLARE_METATYPE(std::vector<olaf::Move>)
Q_DECLARE_METATYPE(std::vector<olaf::Position>)
Q_DECLARE_METATYPE(const olaf::Piece*)
Q_DECLARE_METATYPE(olaf::Move)

namespace olaf
{
namespace test
{

MATCHER_P(IsSameMove, move, "") {
  return ExplainMatchResult(testing::Eq(move.source()), arg.source(), result_listener)
      && ExplainMatchResult(testing::Eq(move.destination()), arg.destination(), result_listener)
      && ExplainMatchResult(testing::Eq(move.is_capture()), arg.is_capture(), result_listener)
      && ExplainMatchResult(testing::Eq(move.is_conversion()), arg.is_conversion(), result_listener)
      && ExplainMatchResult(testing::Eq(move.created_piece()), arg.created_piece(), result_listener);
}

#define QASSERT_THAT(value, matcher) { \
  const ::testing::AssertionResult& __gmock_assertion_result = \
    ::testing::internal::MakePredicateFormatterFromMatcher(matcher)(#value, value); \
  if (!__gmock_assertion_result) { \
    QFAIL(__gmock_assertion_result.message()); \
  } \
}

Move make_move(const Position& source, const Position& destination, const bool is_capture);

ChessBoard parse_fen(const std::string& fen);

} // namespace test
} // namespace olaf

#endif // TEST_UTIL_H

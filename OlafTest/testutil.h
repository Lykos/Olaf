#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <QtTest/qtest.h>
#include <string>

#include "gmock/gmock-generated-matchers.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/position.h"
#include "OlafRules/move.h"

MATCHER_P(IsSameMove, move, "") {
  return ExplainMatchResult(testing::Eq(move.source()), arg.source(), result_listener)
      && ExplainMatchResult(testing::Eq(move.destination()), arg.destination(), result_listener)
      && ExplainMatchResult(testing::Eq(move.is_capture()), arg.is_capture(), result_listener)
      && ExplainMatchResult(testing::Eq(move.is_conversion()), arg.is_conversion(), result_listener)
      && ExplainMatchResult(testing::Eq(move.created_piece()), arg.created_piece(), result_listener);
}

#define QASSERT_THAT(value, matcher) { \
  const AssertionResult& result = \
    ::testing::internal::MakePredicateFormatterFromMatcher(matcher)(#value, value); \
  if (!result) { \
    QFAIL(result.message()); \
  } \
}

Move make_move(const Position& source, const Position& destination, const bool is_capture);

ChessBoard parse_fen(const std::string& fen);

#endif // TEST_UTIL_H

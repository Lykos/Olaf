#ifndef OLAFRULESTEST_TEST_UTIL_H
#define OLAFRULESTEST_TEST_UTIL_H

#include "gmock/gmock-generated-matchers.h"
#include <QtTest/qtest.h>

MATCHER_P(IsSameMove, move, "") {
  return ExplainMatchResult(testing::Eq(move.source()), arg.source(), result_listener)
      && ExplainMatchResult(testing::Eq(move.destination()), arg.destination(), result_listener)
      && ExplainMatchResult(testing::Eq(move.is_capture()), arg.is_capture(), result_listener)
      && ExplainMatchResult(testing::Eq(move.is_conversion()), arg.is_conversion(), result_listener)
      && ExplainMatchResult(testing::Eq(move.created_piece()), arg.created_piece(), result_listener);
}

#endif // OLAFRULESTEST_TEST_UTIL_H

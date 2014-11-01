#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <QtTest/qtest.h>
#include <string>

#include "gmock/gmock-generated-matchers.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/move.h"
#include "olaf/parse/epdposition.h"
#include "olaf/config.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/search/searcherfactory.h"

namespace olaf
{
namespace benchmark
{

#define QASSERT_THAT(value, matcher) { \
  const AssertionResult& __gmock_assertion_result = \
    ::testing::internal::MakePredicateFormatterFromMatcher(matcher)(#value, value); \
  if (!__gmock_assertion_result) { \
    QFAIL(__gmock_assertion_result.message()); \
  } \
}

ChessBoard parse_fen(const std::string& fen);

EpdPosition parse_epd(const std::string& epd);

} // namespace benchmark
} // namespace olaf

#endif // TEST_UTIL_H

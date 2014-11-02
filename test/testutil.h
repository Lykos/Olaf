#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <QtTest/qtest.h>
#include <string>
#include <memory>
#include <vector>

#include "gmock/gmock-generated-matchers.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/move.h"
#include "olaf/rules/piece.h"
#include "olaf/search/perft.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/config.h"

Q_DECLARE_METATYPE(olaf::BitBoard)
Q_DECLARE_METATYPE(olaf::ChessBoard)
Q_DECLARE_METATYPE(olaf::Position)
Q_DECLARE_METATYPE(std::vector<olaf::Perft::PerftResult>)
Q_DECLARE_METATYPE(std::vector<olaf::Move>)
Q_DECLARE_METATYPE(std::vector<olaf::Position>)
Q_DECLARE_METATYPE(const olaf::Piece*)
Q_DECLARE_METATYPE(olaf::Move)
Q_DECLARE_METATYPE(olaf::IncompleteMove)
Q_DECLARE_METATYPE(olaf::TranspositionTableEntry)

namespace olaf
{
namespace test
{

#define QASSERT_THAT(value, matcher) { \
  const ::testing::AssertionResult& __gmock_assertion_result = \
    ::testing::internal::MakePredicateFormatterFromMatcher(matcher)(#value, value); \
  if (!__gmock_assertion_result) { \
    QFAIL(__gmock_assertion_result.message()); \
  } \
}

ChessBoard parse_fen(const std::string& fen);

struct TestFactoryOwner {
  TestFactoryOwner();

  TestFactoryOwner(const Config& config);

  Config config;

  NoThinkingWriter no_thinking_writer;

  SearcherFactory factory;
};

Config test_config();

} // namespace test
} // namespace olaf

#endif // TESTUTIL_H

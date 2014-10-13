#ifndef OLAFTESTUTIL_TESTUTIL_H
#define OLAFTESTUTIL_TESTUTIL_H

#include "gmock/gmock-matchers.h"

#define QASSERT_THAT(value, matcher) { \
  const AssertionResult& result = \
    ::testing::internal::MakePredicateFormatterFromMatcher(matcher)(#value, value); \
  if (!result) { \
    QFAIL(result.message()); \
  } \
}

#endif // OLAFTESTUTIL_TESTUTIL_H

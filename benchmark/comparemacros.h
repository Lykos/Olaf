#ifndef COMPAREMACROS_H
#define COMPAREMACROS_H

#include <QtTest/QtTest>

namespace olaf
{
namespace benchmark
{

#define COMPARE_SIZE(list, expected_size) QCOMPARE((int) (list).size(), (expected_size))
#define COMPARE_INTS(actual, expected) QCOMPARE((unsigned long int) (actual), (unsigned long int) (expected))

} // namespace benchmark
} // namespace olaf

#endif // COMPAREMACROS_H

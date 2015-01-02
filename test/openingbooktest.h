#ifndef OPENINGBOOKTEST_H
#define OPENINGBOOKTEST_H

#include <QObject>

#include "test/autotest.h"

namespace olaf
{
namespace test
{

class OpeningBookTest : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void test_opening_zobrist_hash();

  void test_opening_zobrist_hash_data();
};

DECLARE_TEST(OpeningBookTest)

} // namespace test
} // namespace olaf

#endif // OPENINGBOOKTEST_H


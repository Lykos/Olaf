#ifndef SEARCHERTEST_H
#define SEARCHERTEST_H

#include <QObject>
#include <memory>

#include "autotest.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/search/searcher.h"
#include "olaf/search/nostopper.h"

namespace olaf
{
namespace test
{

class SearcherTest : public QObject
{
  Q_OBJECT

public:
  SearcherTest();

private:
  NoThinkingWriter m_no_thinking_writer;

  std::unique_ptr<Searcher> m_searcher;

  NoStopper m_stopper;

private Q_SLOTS:
  void test_mate();

  void test_mate_in_one();

  void test_stalemate();
};

DECLARE_TEST(SearcherTest)

} // namespace test
} // namespace olaf


#endif // SEARCHERTEST_H

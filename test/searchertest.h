#ifndef SEARCHERTEST_H
#define SEARCHERTEST_H

#include <QObject>
#include <memory>

#include "autotest.h"
#include "olaf/search/nothinkingwriter.h"
#include "olaf/search/searcher.h"
#include "olaf/search/searchcontext.h"
#include "olaf/search/nostopper.h"
#include "test/testutil.h"

namespace olaf
{
namespace test
{

class SearcherTest : public QObject
{
  Q_OBJECT

private:
  TestFactoryOwner m_factory_owner;

  NoThinkingWriter m_no_thinking_writer;

  std::unique_ptr<Searcher> m_searcher;

  NoStopper m_stopper;

  SearchContext m_context;

private Q_SLOTS:
  void init_test_case();

  void test_mate();

  void test_mate_in_one();

  void test_stalemate_data();

  void test_stalemate();
};

DECLARE_TEST(SearcherTest)

} // namespace test
} // namespace olaf


#endif // SEARCHERTEST_H

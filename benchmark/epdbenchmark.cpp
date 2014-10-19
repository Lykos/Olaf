#include "epdbenchmark.h"

#include <cassert>
#include <fstream>
#include <QtTest/QTest>
#include <chrono>
#include <dirent.h>
#include <sstream>

#include "olaf/parse/epdposition.h"
#include "olaf/search/nostopper.h"
#include "testutil.h"

using namespace std;
using namespace chrono;
using namespace testing;

Q_DECLARE_METATYPE(olaf::EpdPosition)

namespace olaf
{
namespace benchmark
{

static const milliseconds c_max_time(120000);
static const string c_epd_extension = ".epd";
static const string c_epd_directory = "epd_files";

static vector<string> list_epd_files(const string& dir_name)
{
  vector<string> result;
  DIR* const dir = opendir(dir_name.c_str());
  if (dir) {
    const struct dirent* entry = readdir(dir);
    while (entry) {
      const string name = entry->d_name;
      if (name.rfind(c_epd_extension) == name.size() - c_epd_extension.size()) {
        result.push_back(dir_name + "/" + name);
      }
      entry = readdir(dir);
    }
    closedir(dir);
  }
  return result;
}

EpdBenchmark::EpdBenchmark():
  m_factory(&m_no_thinking_writer)
{}

EpdBenchmark::~EpdBenchmark()
{}

void EpdBenchmark::initTestCase()
{
  m_searcher.reset(new SimpleTimedSearcher(m_factory.iterative_searcher(), c_max_time));
}

void EpdBenchmark::test_epd()
{
  QFETCH(EpdPosition, position);

  SearchContext context;
  context.board = position.board;
  context.time_mode = SearchContext::TimeMode::BOUNDED;
  NoStopper stopper;
  context.forced_stopper = &stopper;
  context.weak_stopper = &stopper;
  Move move = m_searcher->search(&context).main_variation.back();
  long score = 0;
  auto ContainsMove = Matches(Contains(IsSameMove(move)));
  if (!position.best_moves.empty()) {
    if (ContainsMove(position.best_moves)) {
      push_score(1);
    }
  } else {
    assert(!position.avoid_moves.empty());
    if (!ContainsMove(position.avoid_moves)) {
      push_score(1);
    }
  }
  push_score(score);
}

void EpdBenchmark::test_epd_data()
{
  QTest::addColumn<EpdPosition>("position");

  for (const string& epd_file : list_epd_files(c_epd_directory)) {
    std::unique_ptr<EpdParser> parser = m_factory.epd_parser();
    ifstream file(epd_file);
    string line;
    int i = 1;
    while (getline(file, line)) {
      EpdPosition position;
      assert(parser->parse(line, &position));
      ostringstream oss;
      oss << epd_file << " " << position.id.c_str();
      QTest::newRow(oss.str().c_str()) << position;
      ++i;
    }
  }

} // namespace benchmark
} // namespace olaf
}

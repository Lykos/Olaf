#include "epdbenchmark.h"

#include <cassert>
#include <fstream>
#include <QtTest/QTest>
#include <chrono>
#include <dirent.h>
#include <sstream>

#include "OlafSearching/epdposition.h"
#include "testutil.h"

using namespace std;
using namespace chrono;
using namespace testing;

Q_DECLARE_METATYPE(EpdPosition)

static const milliseconds c_max_time(10);
static const string c_epd_extension = ".epd";
static const string c_epd_directory = "epd_files";

static vector<string> list_epd_files(const string& dir_name)
{
  vector<string> result;
  DIR* const dir = opendir(dir_name.c_str());
  if (dir) {
    const struct dirent* const entry = readdir(dir);
    while (entry) {
      const string name = entry->d_name;
      if (name.rfind(c_epd_extension) == name.size() - c_epd_extension.size()) {
        result.push_back(name);
      }
    }
    closedir(dir);
  }
  return result;
}

EpdBenchmark::EpdBenchmark():
  m_factory(nullptr)
{}

void EpdBenchmark::initTestCase()
{
  m_searcher.reset(new SimpleTimedSearcher(m_factory.iterative_searcher(), c_max_time));
}

void EpdBenchmark::test_epd()
{
  QFETCH(EpdPosition, position);

  Move move;
  NoStopper stopper;
  ChessBoard board(position.board);
  OLAF_BENCHMARK {
    move = m_searcher->search_timed(&board, stopper, stopper).main_variation().back();
  }
  QASSERT_THAT(position.best_moves, Contains(IsSameMove(move)));
}

void EpdBenchmark::test_epd_data()
{
  QTest::addColumn<EpdPosition>("position");

  for (const string& epd_file : list_epd_files(c_epd_directory)) {
    std::unique_ptr<EpdParser> parser = m_factory.epd_parser();
    ifstream file(epd_file);
    string line;
    while (getline(file, line)) {
      EpdPosition position;
      assert(parser->parse(line, &position));
      ostringstream oss;
      oss << epd_file << " " << position.id.c_str();
      QTest::newRow(oss.str().c_str()) << position;
    }
  }
}

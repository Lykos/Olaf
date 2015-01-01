#include "epdbenchmark.h"

#include <cctype>
#include <cassert>
#include <fstream>
#include <QtTest/QTest>
#include <chrono>
#include <dirent.h>
#include <sstream>

#include "olaf/parse/epdposition.h"
#include "olaf/parse/epdparser.h"
#include "olaf/parse/sanparser.h"
#include "olaf/search/nostopper.h"
#include "olaf/search/searchcontext.h"
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

static vector<string> list_epd_files(const string& dir_name)
{
  static const string c_epd_extension = ".epd";
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

static vector<unique_ptr<EpdBenchmark>> create_epd_benchmarks()
{
  vector<unique_ptr<EpdBenchmark>> result;
  static const string c_epd_directory = "epd_files";
  for (const string& epd_file : list_epd_files(c_epd_directory)) {
    result.emplace_back(new EpdBenchmark(epd_file));
    auto_benchmark::add_benchmark(result.back().get());
  }
  return result;
}

static const vector<unique_ptr<EpdBenchmark>> epd_benchmarks = create_epd_benchmarks();

static string file_name_to_class_name(const string& name)
{
  static const char c_underscore = '_';
  static const char c_slash = '/';
  const auto slash_index = name.rfind(c_slash);
  auto it = name.begin() + (slash_index == string::npos ? 0 : slash_index + 1);
  auto end = name.end();
  string result;
  for (; it != end && !isalpha(*it); ++it);
  if (it != end) {
    result.push_back(toupper(*it));
  }
  for (; it != end; ++it) {
    auto next = it + 1;
    if (next != end && *next == c_underscore) {
      result.push_back(toupper(*it));
      ++it; // Overjump next.
    } else if (isalpha(*it)) {
      result.push_back(*it);
    }
  }
  return result;
}

EpdBenchmark::EpdBenchmark(const string& epd_file):
  Benchmark(file_name_to_class_name(epd_file)),
  m_epd_file(epd_file)
{}

EpdBenchmark::~EpdBenchmark()
{}

void EpdBenchmark::initTestCase()
{
  m_factory.reset(new SearcherFactory(&m_writer, config()));
  m_searcher.reset(new SimpleTimedSearcher(m_factory->iterative_searcher(), 40));
}

void EpdBenchmark::test_epd()
{
  QFETCH(EpdPosition, position);

  SearchContext context;
  context.board = position.board;
  context.time_mode = SearchContext::TimeMode::FIXED;
  context.total_time = c_max_time;
  NoStopper stopper;
  context.forced_stopper = &stopper;
  context.weak_stopper = &stopper;
  TranspositionTable transposition_table(0x1000);
  context.transposition_table = &transposition_table;
  PawnTable pawn_table(0x1000);
  context.pawn_table = &pawn_table;
  const vector<Move> main_variation = m_searcher->search(&context).main_variation;
  QVERIFY(!main_variation.empty());
  Move move = main_variation.back();
  long score = 0;
  auto ContainsMove = Matches(Contains(move));
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
  std::unique_ptr<EpdParser> parser = SearcherFactory::epd_parser();
  ifstream file(m_epd_file);
  string line;
  int i = 1;
  while (getline(file, line)) {
    EpdPosition position;
    QVERIFY(parser->parse(line, &position).ok());
    ostringstream oss;
    oss << position.id.c_str();
    QTest::newRow(oss.str().c_str()) << position;
    ++i;
  }
}

} // namespace benchmark
} // namespace olaf

#include "testutil.h"

#include <cassert>
#include <string>
#include <sstream>

#include "olaf/parse/fenparser.h"
#include "olaf/rules/chessboard.h"
#include "olaf/parse/epdposition.h"
#include "olaf/parse/epdparser.h"
#include "olaf/parse/sanparser.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/search/nothinkingwriter.h"

using namespace std;

namespace olaf
{
namespace benchmark
{
static const char c_config[] =
    "search:\n"
    "  time_millis: 2000\n"
    "  min_depth: 1\n"
    "  sequential_depth: 2\n"
    "transposition_table:\n"
    "  size: 65536\n";

ChessBoard parse_fen(const string& fen)
{
  ChessBoard board;
  assert(FenParser::parse(fen, &board));
  return board;
}

TestFactoryOwner::TestFactoryOwner(const Config& config2):
  config(config2),
  factory(&no_thinking_writer, &config)
{}

TestFactoryOwner::TestFactoryOwner():
  TestFactoryOwner(test_config())
{}

Config test_config()
{
  return Config(c_config);
}

EpdPosition parse_epd(const string& epd)
{
  EpdPosition position;
  static const TestFactoryOwner factory_owner;
  assert(factory_owner.factory.epd_parser()->parse(epd, &position));
  return position;
}

} // namespace benchmark
} // namespace olaf

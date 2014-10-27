#include "test/testutil.h"

#include <cassert>
#include <string>
#include <sstream>

#include "olaf/parse/fenparser.h"
#include "olaf/rules/chessboard.h"

using namespace std;

namespace olaf
{
namespace test
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
#ifdef NDEBUG
  FenParser::parse(fen, &board);
#else
  assert(FenParser::parse(fen, &board));
#endif
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

} // namespace test
} // namespace olaf


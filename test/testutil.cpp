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
    "  default_moves_to_play: 40\n"
    "  min_depth: 1\n"
    "  sequential_depth: 2\n"
    "  use_quiescent_search: true\n"
    "transposition_table:\n"
    "  size: 65536\n"
    "move_ordering:\n"
    "  use_hash_move: true\n"
    "  use_see: true\n"
    "  use_killers: true\n";

ChessBoard parse_fen(const string& fen)
{
  ChessBoard board;
#ifdef NDEBUG
  FenParser::parse(fen, &board);
#else
  assert(FenParser::parse(fen, &board).ok());
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


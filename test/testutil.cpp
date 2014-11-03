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
  TestFactoryOwner(Config())
{}

} // namespace test
} // namespace olaf


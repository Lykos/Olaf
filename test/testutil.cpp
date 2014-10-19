#include "testutil.h"

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

Move make_move(const Position& source, const Position& destination, const bool is_capture)
{
  return Move({}, source, destination, is_capture, false, Piece::c_no_piece);
}

ChessBoard parse_fen(const string& fen)
{
  ChessBoard board;
  assert(FenParser::parse(fen, &board));
  return board;

} // namespace test
} // namespace olaf
}

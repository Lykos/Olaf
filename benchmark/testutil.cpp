#include "testutil.h"

#include <cassert>
#include <string>
#include <sstream>

#include "olaf/fenparser.h"
#include "olaf/chessboard.h"
#include "olaf/epdposition.h"
#include "olaf/epdparser.h"
#include "olaf/searcherfactory.h"
#include "olaf/nothinkingwriter.h"

using namespace std;

namespace olaf
{
namespace benchmark
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
}

EpdPosition parse_epd(const string& epd)
{
  EpdPosition position;
  NoThinkingWriter no_thinking_writer;
  SearcherFactory factory(&no_thinking_writer);
  assert(factory.epd_parser()->parse(epd, &position));
  return position;

} // namespace benchmark
} // namespace olaf
}

#include "testutil.h"

#include <cassert>
#include <string>
#include <sstream>

#include "OlafRules/fenparser.h"
#include "OlafRules/chessboard.h"
#include "OlafSearching/epdposition.h"
#include "OlafSearching/epdparser.h"
#include "OlafSearching/searcherfactory.h"
#include "OlafSearching/nothinkingwriter.h"

using namespace std;

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
}

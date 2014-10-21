#include "testutil.h"

#include <cassert>
#include <string>
#include <sstream>

#include "olaf/parse/fenparser.h"
#include "olaf/rules/chessboard.h"
#include "olaf/parse/epdposition.h"
#include "olaf/parse/epdparser.h"
#include "olaf/search/searcherfactory.h"
#include "olaf/search/nothinkingwriter.h"

using namespace std;

namespace olaf
{
namespace benchmark
{

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

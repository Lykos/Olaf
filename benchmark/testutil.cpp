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

EpdPosition parse_epd(const string& epd)
{
  EpdPosition position;
  auto parser = SearcherFactory::epd_parser();
#ifdef NDEBUG
  parser->parse(epd, &position);
#else
  assert(parser->parse(epd, &position).ok());
#endif
  return position;
}

} // namespace benchmark
} // namespace olaf

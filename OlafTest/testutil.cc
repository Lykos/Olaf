#include "testutil.h"

#include <cassert>
#include <string>
#include <sstream>

#include "OlafRules/fenparser.h"
#include "OlafRules/chessboard.h"

using namespace std;

ChessBoard parse_fen(const string& fen)
{
  ChessBoard board;
  assert(FenParser::parse(fen, &board));
  return board;
}

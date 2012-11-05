#include "stupidthinkingwriter.h"
#include "OlafRules/pieceset.h"
#include <sstream>

using namespace std;
using namespace chrono;

StupidThinkingWriter::StupidThinkingWriter(const shared_ptr<ProtocolWriter> &writer):
  m_writer (writer)
{}

void StupidThinkingWriter::output(const ChessBoard &board, const SearchResult &result, const milliseconds &time, int depth)
{
  ostringstream oss;
  int turn_number = board.turn_number();
  int ply = 0;
  if (board.turn_color() == Black) {
    oss << turn_number << ". ... ";
    ++turn_number;
    ++ply;
  }
  for (const Move &move : result.main_variation()) {
    if (ply % 2 == 0) {
      oss << " " << turn_number << ".";
    }
    oss << " " << move.source() << move.destination();
    if (move.is_conversion()) {
      if (move.created_piece() == PieceSet::instance().bishop()->piece_index()) {
        oss << "b";
      } else if (move.created_piece() == PieceSet::instance().knight()->piece_index()) {
        oss << "n";
      } else if (move.created_piece() == PieceSet::instance().queen()->piece_index()) {
        oss << "q";
      } else if (move.created_piece() == PieceSet::instance().rook()->piece_index()) {
        oss << "r";
      }
    }
    ++ply;
  }
  m_writer->thinking_output(depth, result.value(), time.count() / 10, result.nodes(), oss.str());
}

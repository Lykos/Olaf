#include "simplethinkingwriter.h"

#include <sstream>
#include <algorithm>

#include "OlafRules/pieceset.h"

using namespace std;
using namespace chrono;

SimpleThinkingWriter::SimpleThinkingWriter(ProtocolWriter* const writer):
  m_writer(writer)
{}

void SimpleThinkingWriter::output(const ChessBoard &board, const SearchResult &result, const milliseconds &time, int depth)
{
  if (!post()) {
    return;
  }
  ostringstream oss;
  int turn_number = board.turn_number();
  int ply = 0;
  if (board.turn_color() == Color::Black) {
    oss << turn_number << ". ... ";
    ++turn_number;
    ++ply;
  }
  const vector<Move>& moves = result.main_variation;
  for (auto it = moves.crbegin(); it != moves.crend(); ++it) {
    const Move& move = *it;
    if (ply % 2 == 0) {
      oss << " " << turn_number << ".";
    }
    oss << " " << move.source() << move.destination();
    if (move.is_conversion()) {
      if (move.created_piece() == PieceSet::instance().bishop().piece_index()) {
        oss << "b";
      } else if (move.created_piece() == PieceSet::instance().knight().piece_index()) {
        oss << "n";
      } else if (move.created_piece() == PieceSet::instance().queen().piece_index()) {
        oss << "q";
      } else if (move.created_piece() == PieceSet::instance().rook().piece_index()) {
        oss << "r";
      }
    }
    ++ply;
  }
  const int score = board.turn_color() == Color::White ? result.score : -result.score;
  m_writer->thinking_output(depth,
                            score,
                            time.count() / 10,
                            result.nodes,
                            oss.str());
}

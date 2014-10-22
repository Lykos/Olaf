#include "simplethinkingwriter.h"

#include <sstream>
#include <algorithm>

#include "olaf/rules/pieceset.h"
#include "olaf/search/searcher.h"
#include "protocols/protocolwriter.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SimpleThinkingWriter::SimpleThinkingWriter(ProtocolWriter* const writer):
  m_writer(writer)
{}

void SimpleThinkingWriter::output(const ChessBoard& board,
                                  const SearchResult& result,
                                  const milliseconds& time,
                                  const Searcher::depth_t depth)
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
    if (move.is_promotion()) {
      oss << PieceSet::instance().piece(move.created_piece()).symbol(Color::Black);
    }
    ++ply;
  }
  const int score = board.turn_color() == Color::White ? result.score : -result.score;
  m_writer->thinking_output(depth,
                            score,
                            time.count() / 10,
                            result.nodes,
                            oss.str());

} // namespace olaf
}

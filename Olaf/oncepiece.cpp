#include "oncepiece.h"
#include "pieceset.h"

using namespace std;

OncePiece::OncePiece(piece_index_t piece_index, const BitBoard& initial_board, const std::vector<PositionDelta> &directions):
  Piece(piece_index, initial_board),
  m_directions (directions)
{}

vector<Move> OncePiece::moves(const Position &source, const ChessBoard &board, const BitBoard &opponents, const BitBoard &friends) const
{
  vector<Move> result;
  for (const PositionDelta &direction : m_directions) {
    if (source.in_bounds(direction)) {
      Position destination = source + direction;
      if (!friends.get(destination)) {
        Move move (piece_index(), source, destination);
        move.disable_ep();
        if ((board.turn_board().can_castle_q() || board.turn_board().can_castle_k()) && piece_index() == PieceSet::KING_INDEX && source.row() == ground_line(board.turn()) && source.column() == 4) {
          move.forbid_castling();
        }
        if (opponents.get(destination)) {
          move.capture(board.noturn_board().piece_index(destination), destination);
        }
        result.push_back(move);
      }
    }
  }
  return result;
}

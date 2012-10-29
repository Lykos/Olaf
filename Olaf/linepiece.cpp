#include "linepiece.h"
#include "pieceset.h"

using namespace std;

LinePiece::LinePiece(piece_index_t piece_index, const BitBoard& initial_board, const vector<PositionDelta>& directions):
  Piece(piece_index, initial_board),
  m_directions (directions)
{}

vector<Move> LinePiece::moves(const Position &source, const ChessBoard &board, const BitBoard &opponents, const BitBoard &friends) const
{
  vector<Move> result;
  for (const PositionDelta &direction : m_directions) {
    Position current (source);
    while (current.in_bounds(direction) && !opponents.get(current)) {
      current = current + direction;
      if (friends.get(current)) {
        break;
      }
      Move move (piece_index(), source, current);
      move.disable_ep();
      if (board.turn_board().can_castle_q() && piece_index() == PieceSet::ROOK_INDEX && source.row() == ground_line(board.turn()) && source.column() == 0) {
        move.forbid_q_castling();
      }
      if (board.turn_board().can_castle_k() && piece_index() == PieceSet::ROOK_INDEX && source.row() == ground_line(board.turn()) && source.column() == 7) {
        move.forbid_k_castling();
      }
      if (opponents.get(current)) {
        move.capture(board.turn_board().piece_index(current), current);
      }
      result.push_back(move);
    }
  }
  return result;
}

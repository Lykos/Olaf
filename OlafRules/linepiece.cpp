#include "linepiece.h"
#include <utility>

using namespace std;
using namespace rel_ops;

LinePiece::LinePiece(piece_index_t piece_index, const BitBoard& initial_board, const vector<PositionDelta>& directions, bool is_rook):
  Piece(piece_index, initial_board),
  m_directions (directions),
  m_is_rook (is_rook)
{}

vector<Move> LinePiece::moves(const Position &source, const ChessBoard &board) const
{
  vector<Move> result;
  for (const PositionDelta &direction : m_directions) {
    Position current (source);
    while (current.in_bounds(direction) && !board.opponent(current)) {
      current = current + direction;
      if (board.friendd(current)) {
        break;
      }
      Move move (board, piece_index(), source, current);
      if (board.turn_board().can_castle_q() && m_is_rook && source.row() == ground_line(board.turn_color()) && source.column() == 0) {
        move.forbid_q_castling();
      }
      if (board.turn_board().can_castle_k() && m_is_rook && source.row() == ground_line(board.turn_color()) && source.column() == 7) {
        move.forbid_k_castling();
      }
      result.push_back(move);
    }
  }
  return result;
}

bool LinePiece::can_move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  PositionDelta difference = destination - source;
  if (difference.d_row() == 0 && difference.d_column() == 0) {
    return false;
  }
  if (board.friendd(destination)) {
    return false;
  }
  uint_fast8_t length = max(abs(difference.d_row()), abs(difference.d_column()));
  PositionDelta direction (difference.d_row() / length, difference.d_column() / length);
  bool valid_direction = false;
  for (const PositionDelta &dir : m_directions) {
    if (dir == direction) {
      valid_direction = true;
      break;
    }
  }
  if (!valid_direction) {
    return false;
  }
  for (Position position = source + direction; position != destination; position = position + direction) {
    if (board.occupied(position)) {
      return false;
    }
  }
  return true;
}

Move LinePiece::move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  Move result (board, piece_index(), source, destination);
  if (board.turn_board().can_castle_q() && m_is_rook && source.row() == ground_line(board.turn_color()) && source.column() == 0) {
    result.forbid_q_castling();
  }
  if (board.turn_board().can_castle_k() && m_is_rook && source.row() == ground_line(board.turn_color()) && source.column() == 7) {
    result.forbid_k_castling();
  }
  return result;
}

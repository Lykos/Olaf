#include "oncepiece.h"
#include <cassert>

using namespace std;

OncePiece::OncePiece(piece_index_t piece_index, const BitBoard& initial_board, const std::vector<PositionDelta> &directions, bool is_king):
  Piece(piece_index, initial_board),
  m_directions (directions),
  m_is_king (is_king)
{}

vector<Move> OncePiece::moves(const Position &source, const ChessBoard &board) const
{
  vector<Move> result;
  for (const PositionDelta &direction : m_directions) {
    if (source.in_bounds(direction)) {
      Position destination = source + direction;
      if (!board.friendd(destination)) {
        Move move (board, piece_index(), source, destination);
        if ((board.turn_board().can_castle_q() || board.turn_board().can_castle_k()) && m_is_king && source.row() == ground_line(board.turn_color()) && source.column() == 4) {
          move.forbid_castling();
        }
        result.push_back(move);
      }
    }
  }
  if (m_is_king && source.row() == ground_line(board.turn_color()) && source.column() == 4) {
    if (board.turn_board().can_castle_q()
        && !board.occupied(Position(source.row(), 1))
        && !board.occupied(Position(source.row(), 2))
        && !board.occupied(Position(source.row(), 3))) {
      result.push_back(Move(board, source, Position(source.row(), 2)));
    } else if (board.turn_board().can_castle_k()
               && !board.occupied(Position(source.row(), 5))
               && !board.occupied(Position(source.row(), 6))) {
      result.push_back(Move(board, source, Position(source.row(), 6)));
    }
  }
  return result;
}

bool OncePiece::can_move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  if (board.friendd(destination)) {
    return false;
  }
  if (m_is_king && destination.row() == source.row() && source.row() == ground_line(board.turn_color()) && source.column() == 4) {
    if (destination.column() == 2) {
          return board.turn_board().can_castle_q()
              && !board.occupied(Position(ground_line(board.turn_color()), 1))
              && !board.occupied(Position(ground_line(board.turn_color()), 3))
              && !board.occupied(destination);
    } else if (destination.column() == 6) {
      return board.turn_board().can_castle_k()
          && !board.occupied(Position(ground_line(board.turn_color()), 5))
          && !board.occupied(destination);
    }
  }
  PositionDelta direction = destination - source;
  for (const PositionDelta &dir : m_directions) {
    if (dir == direction) {
      return true;
    }
  }
  return false;
}

Move OncePiece::move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  if (m_is_king && destination.row() == source.row() && source.row() == ground_line(board.turn_color()) && source.column() == 4 && abs(source.column() - destination.column()) == 2) {
    return Move(board, source, destination);
  }
  Move result (board, piece_index(), source, destination);
  if ((board.turn_board().can_castle_q() || board.turn_board().can_castle_k()) && m_is_king && source.row() == ground_line(board.turn_color()) && source.column() == 4) {
    result.forbid_castling();
  }
  return result;
}

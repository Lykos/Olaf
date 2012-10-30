#include "oncepiece.h"
#include "pieceset.h"

using namespace std;

OncePiece::OncePiece(piece_index_t piece_index, const BitBoard& initial_board, const std::vector<PositionDelta> &directions):
  Piece(piece_index, initial_board),
  m_directions (directions)
{}

vector<Move> OncePiece::moves(const Position &source, const ChessBoard &board) const
{
  vector<Move> result;
  for (const PositionDelta &direction : m_directions) {
    if (source.in_bounds(direction)) {
      Position destination = source + direction;
      if (!board.friendd(destination)) {
        Move move (board, piece_index(), source, destination);
        move.disable_ep();
        if ((board.turn_board().can_castle_q() || board.turn_board().can_castle_k()) && operator==(*PieceSet::instance().king()) && source.row() == ground_line(board.turn()) && source.column() == 4) {
          move.forbid_castling();
        }
        if (opponents.get(destination)) {
          move.capture(board.noturn_board().piece_index(destination), destination);
        }
        result.push_back(move);
      }
    }
  }
  if (operator==(*PieceSet::instance().king()) && source.row() == ground_line(board.turn()) && source.column() == 4) {
    if (board.turn_board().can_castle_q()) {
      result.push_back(Move(board, source, Position(source.row(), 2)));
    } else if (board.turn_board().can_castle_k()) {
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
  if (operator==(*PieceSet::instance().king()) && destination.row() == source.row() && source.row() == ground_line(board.turn()) && source.column() == 4) {
    if (destination.column() == 2) {
          return board.turn_board().can_castle_q()
              && !board.occupied(Position(ground_line(board.turn()), 1))
              && !board.occupied(Position(ground_line(board.turn()), 3))
              && !board.occupied(destination);
    } else if (destination.column() == 6) {
      return board.turn_board().can_castle_k()
          && !board.occupied(Position(ground_line(board.turn()), 5))
          && !board.occupied(destination);
    }
  }
  PositionDelta direction = destination - source;
  for (PositionDelta &dir : m_directions) {
    if (dir == direction) {
      return true;
    }
  }
  return false;
}

Move OncePiece::move(const Position &source, const Position &destination, const ChessBoard &board) const
{
  if (operator==(*PieceSet::instance().king()) && destination.row() == source.row() && source.row() == ground_line(board.turn()) && source.column() == 4 && abs(source.column() - destination.column()) == 2) {
    return Move(board, source, destination);
  }
  Move result (board, piece_index(), source, destination);
  if ((board.turn_board().can_castle_q() || board.turn_board().can_castle_k()) && operator==(*PieceSet::instance().king()) && source.row() == ground_line(board.turn()) && source.column() == 4) {
    result.forbid_castling();
  }
  return result;
}

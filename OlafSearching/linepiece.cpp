#include "linepiece.h"

#include <utility>

#include "move.h"
#include "movebuilder.h"

using namespace std;
using namespace rel_ops;

LinePiece::LinePiece(const piece_index_t piece_index,
                     const char symbol,
                     const BitBoard& initial_board,
                     const vector<PositionDelta>& directions,
                     const bool is_rook):
  Piece(piece_index, symbol, initial_board),
  m_directions(directions),
  m_is_rook(is_rook)
{}

vector<Move> LinePiece::moves(const Position& source,
                              const ChessBoard& board) const
{
  vector<Move> result;
  for (const PositionDelta& direction : m_directions) {
    Position current(source);
    while (current.in_bounds(direction) && !board.opponent(current)) {
      current = current + direction;
      if (board.friendd(current)) {
        break;
      }
      result.push_back(move(source, current, board));
    }
  }
  return result;
}

bool LinePiece::can_move(const Position& source,
                         const Position& destination,
                         const ChessBoard& board) const
{
  if (!Piece::can_move(source, destination, board)) {
    return false;
  }
  PositionDelta difference = destination - source;
  uint_fast8_t length = max(abs(difference.d_row()), abs(difference.d_column()));
  PositionDelta direction (difference.d_row() / length, difference.d_column() / length);
  bool valid_direction = false;
  for (const PositionDelta& dir : m_directions) {
    if (dir == direction) {
      valid_direction = true;
      break;
    }
  }
  if (!valid_direction) {
    return false;
  }
  for (Position position = source + direction;
       position != destination;
       position = position + direction) {
    if (board.occupied(position)) {
      return false;
    }
  }
  return true;
}

Move LinePiece::move(const Position& source,
                     const Position& destination,
                     const ChessBoard& board) const
{
  MoveBuilder builder(board, source, destination);
  if (forbids_castle_q(source, board)) {
    builder.forbid_q_castling();
  }
  if (forbids_castle_k(source, board)) {
    builder.forbid_k_castling();
  }
  return builder.build();
}

bool LinePiece::forbids_castle_q(const Position& source, const ChessBoard& board) const {
  return board.turn_board().can_castle_q()
      && m_is_rook
      && source.row() == ground_line(board.turn_color())
      && source.column() == Position::c_queens_rook_column;
}

bool LinePiece::forbids_castle_k(const Position& source, const ChessBoard& board) const {
  return board.turn_board().can_castle_k()
      && m_is_rook
      && source.row() == ground_line(board.turn_color())
      && source.column() == Position::c_kings_rook_column;
}

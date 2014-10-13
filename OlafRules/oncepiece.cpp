#include "oncepiece.h"

#include <cassert>

#include "movebuilder.h"

using namespace std;

static bool can_castle_q(const ChessBoard& board)
{
  return board.turn_board().can_castle_q()
      && !board.occupied(Position(ground_line(board.turn_color()), Position::c_queens_knight_column))
      && !board.occupied(Position(ground_line(board.turn_color()), Position::c_queens_bishop_column))
      && !board.occupied(Position(ground_line(board.turn_color()), Position::c_queen_column));
}

static bool can_castle_k(const ChessBoard& board)
{
  return board.turn_board().can_castle_k()
      && !board.occupied(Position(ground_line(board.turn_color()), Position::c_kings_bishop_column))
      && !board.occupied(Position(ground_line(board.turn_color()), Position::c_kings_knight_column));
}

OncePiece::OncePiece(const piece_index_t piece_index,
                     const char symbol,
                     const BitBoard& initial_board,
                     const std::vector<PositionDelta>& directions,
                     const bool is_king):
  Piece(piece_index, symbol, initial_board),
  m_directions (directions),
  m_is_king (is_king)
{}

vector<Move> OncePiece::moves(const Position& source,
                              const ChessBoard& board) const
{
  vector<Move> result;
  for (const PositionDelta& direction : m_directions) {
    if (source.in_bounds(direction)) {
      Position destination = source + direction;
      if (!board.friendd(destination)) {
        result.push_back(move(source, destination, board));
      }
    }
  }
  if (is_king_at_initial_position(source, board)) {
    if (can_castle_q(board)) {
      result.push_back(move(source, Position(source.row(), Position::c_queens_bishop_column), board));
    }
    if (can_castle_k(board)) {
      result.push_back(move(source, Position(source.row(), Position::c_kings_knight_column), board));
    }
  }
  return result;
}

bool OncePiece::can_move(const Position& source,
                         const Position& destination,
                         const ChessBoard& board) const
{
  if (!Piece::can_move(source, destination, board)) {
    return false;
  }
  if (is_castling_move(source, destination, board)) {
    if (destination.column() == Position::c_queens_bishop_column) {
      return can_castle_q(board);
    } else {
      assert(destination.column() == Position::c_kings_knight_column);
      return can_castle_k(board);
    }
  }
  PositionDelta direction = destination - source;
  for (const PositionDelta& dir : m_directions) {
    if (dir == direction) {
      return true;
    }
  }
  return false;
}

Move OncePiece::move(const Position& source, const Position& destination, const ChessBoard& board) const
{
  if (is_castling_move(source, destination, board)) {
    return MoveBuilder::castle(board, source, destination);
  }
  MoveBuilder builder(board, source, destination);
  if (forbids_castle(source, board)) {
    builder.forbid_castling();
  }
  return builder.build();
}

bool OncePiece::is_king_at_initial_position(const Position& position,
                                            const ChessBoard& board) const
{
  return m_is_king
      && position.row() == ground_line(board.turn_color())
      && position.column() == Position::c_king_column;
}

bool OncePiece::is_castling_move(const Position& source,
                                 const Position& destination,
                                 const ChessBoard& board) const
{
  return is_king_at_initial_position(source, board)
      && source.row() == destination.row()
      && abs(source.column() - destination.column()) == 2;
}

bool OncePiece::forbids_castle(const Position& source, const ChessBoard& board) const
{
  return board.turn_board().can_castle()
      && is_king_at_initial_position(source, board);
}


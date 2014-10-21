#include "olaf/rules/oncepiece.h"

#include <algorithm>
#include <cassert>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/movechecker.h"

using namespace std;

namespace olaf
{

static bool can_castle_q(const ChessBoard& board)
{
  static const Piece::piece_index_t c_rook_index =
      PieceSet::c_rook_index;
  const Position::row_t ground = ground_line(board.turn_color());
  const Position rook_position(ground, Position::c_queens_rook_column);
  return board.turn_board().can_castle_q()
      && !board.occupied(Position(ground, Position::c_queens_knight_column))
      && !board.occupied(Position(ground, Position::c_queens_bishop_column))
      && !board.occupied(Position(ground, Position::c_queen_column))
      && board.turn_board().piece_index(rook_position) == c_rook_index;
}

static bool can_castle_k(const ChessBoard& board)
{
  static const Piece::piece_index_t c_rook_index =
      PieceSet::c_rook_index;
  const Position::row_t ground = ground_line(board.turn_color());
  const Position rook_position(ground, Position::c_kings_rook_column);
  return board.turn_board().can_castle_k()
      && !board.occupied(Position(ground, Position::c_kings_bishop_column))
      && !board.occupied(Position(ground, Position::c_kings_knight_column))
      && board.turn_board().piece_index(rook_position) == c_rook_index;
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
  if (board.finished()) {
    return result;
  }
  for (const PositionDelta& direction : m_directions) {
    if (source.in_bounds(direction)) {
      Position destination = source + direction;
      if (!board.friendd(destination)) {
        result.push_back(MoveChecker::complete(source, destination, board));
      }
    }
  }
  if (is_king_at_initial_position(source, board)) {
    if (can_castle_q(board)) {
      result.push_back(MoveChecker::complete(source, Position(source.row(), Position::c_queens_bishop_column), board));
    }
    if (can_castle_k(board)) {
      result.push_back(MoveChecker::complete(source, Position(source.row(), Position::c_kings_knight_column), board));
    }
  }
  return result;
}

bool OncePiece::can_move(const IncompleteMove incomplete_move,
                         const ChessBoard& board) const
{
  if (!Piece::can_move(incomplete_move, board)) {
    return false;
  }
  const Position dst(incomplete_move.destination());
  if (is_castling_move(incomplete_move, board)) {
    if (dst.column() == Position::c_queens_bishop_column) {
      return can_castle_q(board);
    } else {
      assert(dst.column() == Position::c_kings_knight_column);
      return can_castle_k(board);
    }
  }
  const PositionDelta direction = dst - incomplete_move.source();
  return find(m_directions.begin(), m_directions.end(), direction) != m_directions.end();
}

bool OncePiece::is_king_at_initial_position(const Position& position,
                                            const ChessBoard& board) const
{
  return m_is_king
      && position.row() == ground_line(board.turn_color())
      && position.column() == Position::c_king_column;
}

bool OncePiece::is_castling_move(const IncompleteMove incomplete_move,
                                 const ChessBoard& board) const
{
  const Position dst(incomplete_move.destination());
  const Position src(incomplete_move.source());
  return is_king_at_initial_position(src, board)
      && src.row() == dst.row()
      && abs(src.column() - dst.column()) == 2;
}

} // namespace olaf


#include "olaf/rules/pawn.h"

#include <algorithm>

#include "olaf/rules/move.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"

using namespace std;

namespace olaf
{

Pawn::Pawn(const piece_index_t piece_index,
           const char symbol,
           const BitBoard& initial_board,
           const std::vector<piece_index_t>& conversions):
  Piece(piece_index, symbol, initial_board),
  m_promotions (conversions)
{}

static const array<PositionDelta, 2> sidewards_directions = {{
  PositionDelta(0, 1),
  PositionDelta(0, -1)
}};

static BitBoard capturable(const ChessBoard& board)
{
  return board.opponents() | board.king_captures() | board.ep_captures();
}

std::vector<Move> Pawn::moves(const Position& source,
                              const ChessBoard& board) const
{
  vector<Move> result;
  const Color color = board.turn_color();
  const Position& simple_move_destination =
      source + forward_direction(color);
  // Check if square is free
  if (!board.occupied(simple_move_destination)) {
    // Handle conversion, if necessary.
    if (simple_move_destination.row() == promotion_row(color)) {
      add_conversion_moves(&result, board, source, simple_move_destination);
    } else {
      result.emplace_back(Move::complete(source, simple_move_destination, board));
      if (source.row() == pawn_row(color)) {
        const Position& double_move_destination =
            simple_move_destination + forward_direction(color);
        if (!board.occupied(double_move_destination)) {
          result.emplace_back(Move::complete(source, double_move_destination, board));
        }
      }
    }
  }
  const BitBoard capturable2 = capturable(board);
  for (const PositionDelta& sidewards : sidewards_directions) {
    if (!source.in_bounds(sidewards)) {
      continue;
    }
    Position capture_destination = source + forward_direction(color) + sidewards;
    // Check if capture is possible
    if ((BitBoard(capture_destination) & capturable2) != 0) {
      if (capture_destination.row() == promotion_row(color)) {
        add_conversion_moves(&result, board, source, capture_destination);
      } else {
        result.emplace_back(Move::complete(source, capture_destination, board));
      }
    }
  }
  return result;
}

void Pawn::add_conversion_moves(vector<Move>* const moves,
                                const ChessBoard& board,
                                const Position& source,
                                const Position& destination) const
{
  for (piece_index_t piece_index : m_promotions) {
    moves->emplace_back(Move::complete_promotion(source, destination, piece_index, board));
  }
}

bool Pawn::can_move(const Move move,
                    const ChessBoard& board) const
{
  if (!Piece::can_move(move, board)) {
    return false;
  }
  const Color color = board.turn_color();
  const Position dst(move.destination());
  if (move.is_promotion() != (dst.row() == promotion_row(color))) {
    return false;
  }
  if (move.is_promotion()
      && find(m_promotions.begin(), m_promotions.end(), move.created_piece()) == m_promotions.end()) {
    return false;
  }
  const PositionDelta& delta = forward_direction(board.turn_color());
  const Position src(move.source());
  const Position& step = src + delta;
  // Handle capture.
  if (dst.row() == step.row()
      && abs(dst.column() - step.column()) == 1) {
    return (capturable(board) & BitBoard(dst)) != 0;
  }
  if (dst.column() != step.column()) {
    return false;
  }
  // blocked pawn
  if (board.occupied(step)) {
    return false;
  }
  // valid single step
  if (dst == step) {
    return true;
  }
  // double step
  if (src.row() != pawn_row(board.turn_color())) {
    return false;
  }
  if (board.occupied(dst)) {
    return false;
  }
  const Position& two_step = step + delta;
  return dst == two_step;
}

} // namespace olaf

#include "olaf/rules/pawn.h"

#include <algorithm>

#include "olaf/rules/move.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/magicmoves.h"
#include "olaf/rules/magicnumbers.h"

using namespace std;

namespace olaf
{

Pawn::Pawn(const piece_index_t piece_index,
           const char symbol,
           const BitBoard& initial_board,
           const PieceSet::PromotionArray& promitions):
  Piece(piece_index, symbol, initial_board),
  m_promotions(promitions)
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
  if (board.finished()) {
    return result;
  }
  const BitBoard bitboard = MagicMoves::moves_pawn(source, board);
  if (bitboard & BitBoard(MagicNumbers::c_promotion_rows[static_cast<int>(board.turn_color())])) {
    for (const Position& destination : bitboard.positions()) {
      add_conversion_moves(&result, board, source, destination);
    }
  } else {
    for (const Position& destination : bitboard.positions()) {
      result.push_back(MoveChecker::complete(source, destination, board));
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
    moves->emplace_back(MoveChecker::complete_promotion(source, destination, piece_index, board));
  }
}

bool Pawn::could_move(const IncompleteMove incomplete_move,
                      const ChessBoard& board) const
{
  const Color color = board.turn_color();
  const Position dst(incomplete_move.destination());
  if (incomplete_move.is_promotion() != (dst.row() == promotion_row(color))) {
    return false;
  }
  if (incomplete_move.is_promotion()
      && find(m_promotions.begin(), m_promotions.end(), incomplete_move.created_piece()) == m_promotions.end()) {
    return false;
  }
  const PositionDelta& delta = forward_direction(board.turn_color());
  const Position src(incomplete_move.source());
  const Position& step = src + delta;
  // Handle capture.
  if (dst.row() == step.row()
      && abs(dst.column() - step.column()) == 1) {
    return capturable(board) & BitBoard(dst);
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

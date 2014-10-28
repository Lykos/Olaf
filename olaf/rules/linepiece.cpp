#include "olaf/rules/linepiece.h"

#include <cassert>
#include <algorithm>
#include <utility>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/magicmoves.h"

using namespace std;
using namespace rel_ops;

namespace olaf
{

LinePiece::LinePiece(const piece_index_t piece_index,
                     const char symbol,
                     const BitBoard& initial_board,
                     const vector<PositionDelta>& directions):
  Piece(piece_index, symbol, initial_board),
  m_directions(directions)
{}

vector<Move> LinePiece::moves(const Position& source,
                              const ChessBoard& board) const
{
  vector<Move> result;
  if (board.finished()) {
    return result;
  }
  BitBoard bitboard;
  if (piece_index() == PieceSet::c_rook_index) {
    bitboard = MagicMoves::magic_moves_rook(source, board.occupied(), board.friends());
  } else if (piece_index() == PieceSet::c_bishop_index) {
    bitboard = MagicMoves::magic_moves_bishop(source, board.occupied(), board.friends());
  } else {
    assert(piece_index() == PieceSet::c_queen_index);
    bitboard = MagicMoves::magic_moves_queen(source, board.occupied(), board.friends());
  }
  for (const Position& destination : bitboard.positions()) {
    result.push_back(MoveChecker::complete(source, destination, board));
  }
  return result;
}

bool LinePiece::could_move(const IncompleteMove incomplete_move,
                           const ChessBoard& board) const
{
  const Position src(incomplete_move.source());
  const Position dst(incomplete_move.destination());
  const PositionDelta difference = dst - src;
  const PositionDelta direction = difference.unit();
  if (!can_xray(direction)) {
    return false;
  }
  for (Position position = src + direction;
       position != dst;
       position = position + direction) {
    if (board.occupied(position)) {
      return false;
    }
  }
  return true;
}

bool LinePiece::can_xray(const PositionDelta& direction) const
{
  return find(m_directions.begin(), m_directions.end(), direction) != m_directions.end();
}

} // namespace olaf

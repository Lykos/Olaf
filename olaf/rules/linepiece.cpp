#include "olaf/rules/linepiece.h"

#include <utility>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"

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
  for (const PositionDelta& direction : m_directions) {
    Position current(source);
    while (current.in_bounds(direction) && !board.opponent(current)) {
      current = current + direction;
      if (board.friendd(current)) {
        break;
      }
      result.push_back(MoveChecker::complete(source, current, board));
    }
  }
  return result;
}

bool LinePiece::can_move(const IncompleteMove incomplete_move,
                         const ChessBoard& board) const
{
  const Position src(incomplete_move.source());
  const Position dst(incomplete_move.destination());
  if (!Piece::can_move(incomplete_move, board)) {
    return false;
  }
  const PositionDelta difference = dst - src;
  const uint_fast8_t length = max(abs(difference.d_row()), abs(difference.d_column()));
  if (difference.d_row() % length != 0 || difference.d_column() % length != 0) {
    return false;
  }
  const PositionDelta direction(difference.d_row() / length, difference.d_column() / length);
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
  for (Position position = src + direction;
       position != dst;
       position = position + direction) {
    if (board.occupied(position)) {
      return false;
    }
  }
  return true;
}

} // namespace olaf

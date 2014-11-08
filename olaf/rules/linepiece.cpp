#include "olaf/rules/linepiece.h"

#include <algorithm>
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

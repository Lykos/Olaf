#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"
#include "olaf/rules/positiondelta.h"
#include "olaf/rules/move.h"
#include <vector>

namespace olaf
{

/**
 * @brief The LinePiece class represents pieces that move along a line like the rook, the queen or the bishop.
 */
class LinePiece : public Piece
{
public:
  LinePiece(piece_index_t piece_index,
            char symbol,
            const BitBoard& initial_board,
            const std::vector<PositionDelta>& directions);

  std::vector<Move> moves(const Position& source,
                          const ChessBoard& board) const override;

  bool can_move(IncompleteMove incomplete_move,
                const ChessBoard& board) const override;

private:
  const std::vector<PositionDelta> m_directions;
};

} // namespace olaf

#endif // LINEPIECE_H

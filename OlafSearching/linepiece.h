#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "piece.h"
#include "position.h"
#include "positiondelta.h"
#include "move.h"
#include <vector>

/**
 * @brief The LinePiece class represents pieces that move along a line like the rook, the queen or the bishop.
 */
class LinePiece : public Piece
{
public:
  LinePiece(piece_index_t piece_index,
            char symbol,
            const BitBoard& initial_board,
            const std::vector<PositionDelta>& directions,
            bool is_rook);

  std::vector<Move> moves(const Position& source,
                          const ChessBoard& board) const override;

  bool can_move(const Position& source,
                const Position& destination,
                const ChessBoard& board) const override;

  Move move(const Position& source,
            const Position& destination,
            const ChessBoard& board) const override;

private:
  bool forbids_castle_q(const Position& source, const ChessBoard& board) const;

  bool forbids_castle_k(const Position& source, const ChessBoard& board) const;

  const std::vector<PositionDelta> m_directions;

  const bool m_is_rook;
};

#endif // LINEPIECE_H

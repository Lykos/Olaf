#ifndef ONCEPIECE_H
#define ONCEPIECE_H

#include "move.h"
#include "bitboard.h"
#include "piece.h"
#include "color.h"

/**
 * @brief The OncePiece class represents a piece that can move only once in each
 *        direction, e.g. king or knight.
 */
class OncePiece : public Piece
{
public:
  OncePiece(piece_index_t piece_index,
            char symbol,
            const BitBoard& initial_board,
            const std::vector<PositionDelta>& directions,
            bool is_king);

  std::vector<Move> moves(const Position& source,
                          const ChessBoard& board) const;

  bool can_move(const Position& source,
                const Position& destination,
                const ChessBoard& board) const override;

  Move move(const Position& source,
            const Position& destination,
            const ChessBoard& board) const override;

  Move castle_q(Color) const;

  Move castle_k(Color) const;

private:
  /**
   * @brief is_king_at_initial_position returns true iff this piece is a
   *        king at its initial position.
   */
  bool is_king_at_initial_position(const Position& position,
                                   const ChessBoard& board) const;

  bool is_castling_move(const Position& source,
                        const Position& destination,
                        const ChessBoard& board) const;

  bool forbids_castle(const Position& source, const ChessBoard& board) const;

  std::vector<PositionDelta> m_directions;

  bool m_is_king;
};

#endif // ONCEPIECE_H

#ifndef PAWN_H
#define PAWN_H

#include "color.h"
#include "piece.h"
#include <vector>
#include <cstddef>

class MoveBuilder;

class Pawn : public Piece
{
public:
  Pawn(piece_index_t piece_index,
       char symbol,
       const BitBoard& initial_board,
       const std::vector<piece_index_t>& conversions);

  std::vector<Move> moves(const Position& source,
                          const ChessBoard& board) const;

  bool can_move(const Position& source,
                const Position& destination,
                const ChessBoard& board) const override;

  bool can_move(const Position& source,
                const Position& destination,
                const ChessBoard& board,
                piece_index_t conversion) const;

  Move move(const Position& source,
            const Position& destination,
            const ChessBoard& board) const override;

  Move move(const Position& source,
            const Position& destination,
            const ChessBoard& board,
            piece_index_t conversion) const;

  /**
   * @brief add_conversions adds all moves that are based upon the given base move combined with a conversion action.
   * @param moves
   * @param base_move
   * @param position
   */
  void add_conversion_moves(std::vector<Move>* moves,
                            const MoveBuilder& base_move,
                            const Position& position) const;

private:
  bool internal_can_move(const Position& source,
                         const Position& destination,
                         const ChessBoard& board) const;

  std::vector<piece_index_t> m_conversions;
};

#include "move.h"

#endif // PAWN_H

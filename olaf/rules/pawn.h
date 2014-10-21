#ifndef PAWN_H
#define PAWN_H

#include "color.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/pieceset.h"
#include <vector>
#include <cstddef>

namespace olaf
{

class Move;

class Pawn : public Piece
{
public:
  Pawn(piece_index_t piece_index,
       char symbol,
       const BitBoard& initial_board,
       const PieceSet::PromotionArray& conversions);

  std::vector<Move> moves(const Position& source,
                          const ChessBoard& board) const;

  bool can_move(IncompleteMove incomplete_move,
                const ChessBoard& board) const override;

private:
  /**
   * @brief add_conversions adds all moves that are based upon the given base move combined with a conversion action.
   */
  void add_conversion_moves(std::vector<Move>* moves,
                            const ChessBoard& board,
                            const Position& source,
                            const Position& destination) const;

  const PieceSet::PromotionArray m_promotions;
};

} // namespace olaf

#include "olaf/rules/move.h"

#endif // PAWN_H

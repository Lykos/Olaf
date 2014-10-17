#ifndef CONVERSIONACTION_H
#define CONVERSIONACTION_H

#include "moveaction.h"
#include "pieceset.h"

/**
 * @brief The ConversionAction class represents the action of converting a pawn to another piece.
 */
class ConversionAction : public MoveAction
{
public:
  /**
   * @brief ConversionAction
   * @param position
   * @param removed_piece
   * @param created_piece
   */
  ConversionAction(const Position &position,
                   PieceSet::piece_index_t removed_piece,
                   PieceSet::piece_index_t created_piece);

  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;

  int priority() const override;

private:
  const Position m_position;

  const PieceSet::piece_index_t m_removed_piece;

  const PieceSet::piece_index_t m_created_piece;

};

#endif // CONVERSIONACTION_H

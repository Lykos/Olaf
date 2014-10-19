#ifndef CAPTUREACTION_H
#define CAPTUREACTION_H

#include "moveaction.h"
#include "colorboard.h"
#include "chessboard.h"
#include "pieceset.h"

namespace olaf
{

/**
 * @brief The CaptureAction class represents the action
 *        of capturing a piece.
 */
class CaptureAction : public MoveAction
{
public:
  CaptureAction(const Position& victim_position,
                PieceSet::piece_index_t victim_index);

  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;

  int priority() const override;

private:
  const Position m_victim_position;

  const PieceSet::piece_index_t m_victim_index;
};

} // namespace olaf

#endif // CAPTUREACTION_H

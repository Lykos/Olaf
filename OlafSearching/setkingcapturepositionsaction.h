#ifndef SETKINGCAPTUREPOSITIONSACTION_H
#define SETKINGCAPTUREPOSITIONSACTION_H

#include <memory>
#include <vector>

#include "moveaction.h"
#include "position.h"

class SetKingCapturePositionsAction : public MoveAction
{
public:
  SetKingCapturePositionsAction(const std::vector<Position>& king_capture_positions,
                                const Position& king_victim_position);

  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;

  int priority() const override;

private:
  const std::vector<Position> m_new_king_capture_positions;

  const Position m_new_king_victim_position;

  std::vector<Position> m_old_king_capture_positions;

  Position m_old_king_victim_position;
};

#endif // SETKINGCAPTUREPOSITIONSACTION_H

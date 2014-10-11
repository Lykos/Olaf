#ifndef EPENABLEACTION_H
#define EPENABLEACTION_H

#include "colorboard.h"
#include "moveaction.h"
#include "position.h"

class ChessBoard;

/**
 * @brief The EpEnableAction class represents a pawn double move which enables en passent capture.
 */
class EpEnableAction : public MoveAction
{
public:
  EpEnableAction(const Position& new_ep_capture_position,
                 const Position& new_ep_victim_position);

  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

private:
  bool m_old_ep_possible;

  Position m_old_ep_capture_position;

  Position m_old_ep_victim_position;

  const Position m_new_ep_capture_position;

  const Position m_new_ep_victim_position;

};

#include "chessboard.h"

#endif // EPENABLEACTION_H

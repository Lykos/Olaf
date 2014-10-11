#ifndef EPDISABLEACTION_H
#define EPDISABLEACTION_H

#include <memory>

#include "moveaction.h"
#include "chessboard.h"

class EpDisableAction : public MoveAction
{
public:
  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;

private:
  bool m_old_ep_possible;
};

#endif // EPDISABLEACTION_H

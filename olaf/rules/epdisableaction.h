#ifndef EPDISABLEACTION_H
#define EPDISABLEACTION_H

#include <memory>

#include "olaf/rules/moveaction.h"
#include "olaf/rules/chessboard.h"

namespace olaf
{

class EpDisableAction : public MoveAction
{
public:
  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;

  int priority() const override;

private:
  bool m_old_ep_possible;
};

} // namespace olaf

#endif // EPDISABLEACTION_H

#ifndef EPDISABLEACTION_H
#define EPDISABLEACTION_H

#include "moveaction.h"
#include "chessboard.h"

class EpDisableAction : public MoveAction
{
public:
  void execute(ChessBoard &chess_board);

  void undo(ChessBoard &chess_board);

private:
  bool m_old_ep_possible;

};

#endif // EPDISABLEACTION_H

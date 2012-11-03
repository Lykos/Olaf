#include "epdisableaction.h"

void EpDisableAction::execute(ChessBoard &chess_board)
{
  m_old_ep_possible = chess_board.ep_possible();
  chess_board.ep_possible(false);
}

void EpDisableAction::undo(ChessBoard &chess_board)
{
  chess_board.ep_possible(m_old_ep_possible);
}

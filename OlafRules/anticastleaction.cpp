#include "anticastleaction.h"

AntiCastleAction::AntiCastleAction(const bool forbid_castle_q, const bool forbid_castle_k):
  m_forbid_castle_q(forbid_castle_q),
  m_forbid_castle_k(forbid_castle_k)
{}

void AntiCastleAction::execute(ChessBoard* const chess_board)
{
  ColorBoard& color_board = chess_board->turn_board();
  m_old_can_castle_q = color_board.can_castle_q();
  m_old_can_castle_k = color_board.can_castle_k();
  color_board.can_castle_q(m_old_can_castle_q && !m_forbid_castle_q);
  color_board.can_castle_k(m_old_can_castle_k && !m_forbid_castle_k);
}

void AntiCastleAction::undo(ChessBoard* const chess_board)
{
  ColorBoard& color_board = chess_board->turn_board();
  color_board.can_castle_q(m_old_can_castle_q);
  color_board.can_castle_k(m_old_can_castle_k);
}

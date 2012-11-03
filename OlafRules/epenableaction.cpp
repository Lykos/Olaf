#include "epenablaction.h"

EpEnableAction::EpEnableAction(Position new_ep_capture_position, Position new_ep_victim_position):
  m_new_ep_capture_position (new_ep_capture_position),
  m_new_ep_victim_position (new_ep_victim_position)
{}

void EpEnableAction::execute(ChessBoard& chess_board)
{
  m_old_ep_possible = chess_board.ep_possible();
  m_old_ep_capture_position = chess_board.ep_capture_position();
  m_old_ep_victim_position = chess_board.ep_victim_position();
  chess_board.ep_possible(true);
  chess_board.ep_capture_position(m_new_ep_capture_position);
  chess_board.ep_victim_position(m_new_ep_victim_position);
}

void EpEnableAction::undo(ChessBoard& chess_board)
{
  chess_board.ep_capture_position(m_old_ep_capture_position);
  chess_board.ep_victim_position(m_old_ep_victim_position);
  chess_board.ep_possible(m_old_ep_possible);
}

#include "pawndoublemove.h"

PawnDoubleMove::PawnDoubleMove(ColorBoard::piece_index_t piece_index, Position source, Position destination, Position new_ep_capture_position, Position new_ep_victim_position):
  m_simple_move (piece_index, source, destination),
  m_new_ep_capture_position (new_ep_capture_position),
  m_new_ep_victim_position (new_ep_victim_position)
{}

void PawnDoubleMove::execute(ChessBoard& chess_board)
{
  m_old_ep_capture_position = chess_board.ep_capture_position();
  m_old_ep_victim_position = chess_board.ep_victim_position();
  m_simple_move.execute(chess_board);
  chess_board.ep_possible(true);
  chess_board.ep_capture_position(m_new_ep_capture_position);
  chess_board.ep_victim_position(m_new_ep_victim_position);
}

void PawnDoubleMove::undo(ChessBoard& chess_board)
{
  m_simple_move.undo(chess_board);
  chess_board.ep_capture_position(m_old_ep_capture_position);
  chess_board.ep_victim_position(m_old_ep_victim_position);
}

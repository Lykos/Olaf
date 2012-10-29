#include "anticastlemove.h"

AntiCastleMove::AntiCastleMove(ColorBoard::piece_index_t piece_index, const Position& source, const Position& destination, bool new_can_castle_q, bool new_can_castle_k):
  m_simple_move (piece_index, source, destination),
  m_new_can_castle_q (new_can_castle_q),
  m_new_can_castle_k (new_can_castle_k)
{}

void AntiCastleMove::execute(ChessBoard &chess_board)
{
  ColorBoard& color_board = chess_board.turn_board();
  m_old_can_castle_q = color_board.can_castle_q();
  m_old_can_castle_k = color_board.can_castle_k();
  m_simple_move.execute(chess_board);
  color_board.can_castle_q(m_new_can_castle_q);
  color_board.can_castle_k(m_new_can_castle_k);
}

void AntiCastleMove::undo(ChessBoard &chess_board)
{
  m_simple_move.undo(chess_board);
  ColorBoard& color_board = chess_board.turn_board();
  color_board.can_castle_q(m_old_can_castle_q);
  color_board.can_castle_k(m_old_can_castle_k);
}

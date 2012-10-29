#include "castlemove.h"

CastleMove::CastleMove(const SimpleMoveAction &king_move, const SimpleMoveAction &rook_move):
  m_king_move (king_move),
  m_rook_move (rook_move)
{}

void CastleMove::execute(ChessBoard &chess_board)
{
  ColorBoard& color_board = chess_board.turn_board();
  m_old_can_castle_q = color_board.can_castle_q();
  m_old_can_castle_k = color_board.can_castle_k();
  m_king_move.execute(chess_board);
  m_rook_move.execute(chess_board);
  color_board.can_castle_q(false);
  color_board.can_castle_k(false);
}

void CastleMove::undo(ChessBoard &chess_board)
{
  m_rook_move.undo(chess_board);
  m_king_move.undo(chess_board);
  ColorBoard& color_board = chess_board.turn_board();
  color_board.can_castle_q(m_old_can_castle_q);
  color_board.can_castle_k(m_old_can_castle_k);
}

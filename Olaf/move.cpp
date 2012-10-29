#include "move.h"

Move::Move(MoveAction* move_action):
  m_move_ptr (move_action)
{}

void Move::execute(ChessBoard& chess_board)
{
  m_move_ptr->execute(chess_board);
  chess_board.flip_turn();
}

void Move::undo(ChessBoard& chess_board)
{
  chess_board.flip_turn();
  m_move_ptr->execute(chess_board);
}

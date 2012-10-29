#include "turnflipaction.h"

void TurnFlipAction::execute(ChessBoard &chess_board)
{
  chess_board.flip_turn();
}

void TurnFlipAction::undo(ChessBoard &chess_board)
{
  chess_board.flip_turn();
}

#include "turnflipaction.h"

void TurnFlipAction::execute(ChessBoard* const chess_board)
{
  chess_board->next_turn();
}

void TurnFlipAction::undo(ChessBoard* const chess_board)
{
  chess_board->previous_turn();
}

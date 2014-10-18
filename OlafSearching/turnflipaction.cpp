#include "turnflipaction.h"

void TurnFlipAction::execute(ChessBoard* const chess_board)
{
  chess_board->next_turn();
}

void TurnFlipAction::undo(ChessBoard* const chess_board)
{
  chess_board->previous_turn();
}

std::unique_ptr<MoveAction> TurnFlipAction::copy() const
{
  return std::unique_ptr<MoveAction>(new TurnFlipAction(*this));
}

int TurnFlipAction::priority() const
{
  return MoveAction::TURN_FLIP_ACTION_PRIORITY;
}


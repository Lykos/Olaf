#ifndef TURNFLIPACTION_H
#define TURNFLIPACTION_H

#include "moveaction.h"
#include "chessboard.h"

class TurnFlipAction : public MoveAction
{
public:
  void execute(ChessBoard* chess_board);

  void undo(ChessBoard* chess_board);

};

#endif // TURNFLIPACTION_H

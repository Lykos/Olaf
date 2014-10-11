#ifndef TURNFLIPACTION_H
#define TURNFLIPACTION_H

#include "moveaction.h"
#include "chessboard.h"

class TurnFlipAction : public MoveAction
{
public:
  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;
};

#endif // TURNFLIPACTION_H

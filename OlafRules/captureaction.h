#ifndef CAPTUREACTION_H
#define CAPTUREACTION_H

#include "moveaction.h"
#include "colorboard.h"
#include "chessboard.h"
#include "pieceset.h"

class CaptureAction : public MoveAction
{
public:
  CaptureAction(const Position&, PieceSet::piece_index_t);

  void execute(ChessBoard &chess_board);

  void undo(ChessBoard &chess_board);

private:
  Position m_victim_position;

  PieceSet::piece_index_t m_victim_index;

};

#endif // CAPTUREACTION_H

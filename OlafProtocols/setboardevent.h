#ifndef SETBOARDEVENT_H
#define SETBOARDEVENT_H

#include "OlafRules/chessboard.h"
#include "engineevent.h"

class SetBoardEvent : public EngineEvent
{
public:
  explicit SetBoardEvent(const ChessBoard& board);

  void execute(EngineState* engine_state) override;

private:
  ChessBoard m_board;
};

#endif // SETBOARDEVENT_H

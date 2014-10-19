#ifndef SETBOARDEVENT_H
#define SETBOARDEVENT_H

#include "OlafSearching/chessboard.h"
#include "engineevent.h"

namespace olaf
{

class SetBoardEvent : public EngineEvent
{
public:
  explicit SetBoardEvent(const ChessBoard& board);

  void execute(EngineState* engine_state) override;

private:
  ChessBoard m_board;
};

} // namespace olaf

#endif // SETBOARDEVENT_H

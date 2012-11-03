#ifndef ENGINESTATE_H
#define ENGINESTATE_H

#include "chessboard.h"

class EngineState
{
public:
  EngineState();

private:
  ChessBoard m_board;

  volatile bool m_my_turn;

};

#endif // ENGINESTATE_H

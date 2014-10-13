#include "setboardevent.h"

#include "OlafRules/chessboard.h"
#include "enginestate.h"
#include "boardstate.h"

SetBoardEvent::SetBoardEvent(const ChessBoard& board):
  m_board(board)
{}


void SetBoardEvent::execute(EngineState* const engine_state)
{
  engine_state->board_state().set_board(m_board);
}

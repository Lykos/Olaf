#include "setboardevent.h"

#include "OlafSearching/chessboard.h"
#include "enginestate.h"
#include "boardstate.h"

namespace olaf
{

SetBoardEvent::SetBoardEvent(const ChessBoard& board):
  m_board(board)
{}


void SetBoardEvent::execute(EngineState* const engine_state)
{
  engine_state->board_state().set_board(m_board);

} // namespace olaf
}

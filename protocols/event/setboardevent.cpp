#include "protocols/event/setboardevent.h"

#include "olaf/rules/chessboard.h"
#include "protocols/enginestate.h"
#include "protocols/boardstate.h"

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

#include "moveevent.h"

#include "boardstate.h"

namespace olaf
{

MoveEvent::MoveEvent(const Move &move):
  m_move(move)
{}

void MoveEvent::execute(EngineState* const engine_state)
{
  engine_state->flip_turn();
  engine_state->board_state().move(m_move);

} // namespace olaf
}

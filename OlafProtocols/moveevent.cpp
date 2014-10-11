#include "moveevent.h"

MoveEvent::MoveEvent(const Move &move):
  m_move(move)
{}

void MoveEvent::execute(EngineState* const engine_state)
{
  engine_state->flip_turn();
}

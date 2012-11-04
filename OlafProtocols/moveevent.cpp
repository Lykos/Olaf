#include "moveevent.h"

MoveEvent::MoveEvent(const Move &move):
  m_move (move)
{}

void MoveEvent::execute(EngineState &engine_state)
{
  engine_state.my_turn(engine_state.my_turn());
}

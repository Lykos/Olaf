#include "myturnflipevent.h"

MyTurnFlipEvent::MyTurnFlipEvent(const bool value):
  m_value(value)
{}

void MyTurnFlipEvent::execute(EngineState* const engine_state)
{
  engine_state->my_turn(m_value);
}

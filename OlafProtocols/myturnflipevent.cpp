#include "myturnflipevent.h"

MyTurnFlipEvent::MyTurnFlipEvent(bool value):
  m_value (value)
{}

void MyTurnFlipEvent::execute(EngineState &engine_state)
{
  engine_state.my_turn(m_value);
}

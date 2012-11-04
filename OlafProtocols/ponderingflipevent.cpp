#include "ponderingflipevent.h"

PonderingFlipEvent::PonderingFlipEvent(bool value):
  m_value (value)
{}

void PonderingFlipEvent::execute(EngineState &engine_state)
{
  engine_state.pondering(m_value);
}

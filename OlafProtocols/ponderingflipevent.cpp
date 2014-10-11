#include "ponderingflipevent.h"

PonderingFlipEvent::PonderingFlipEvent(const bool value):
  m_value (value)
{}

void PonderingFlipEvent::execute(EngineState* const engine_state)
{
  engine_state->pondering(m_value);
}

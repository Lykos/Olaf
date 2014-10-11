#include "forceflipevent.h"

ForceFlipEvent::ForceFlipEvent(const bool value):
  m_value(value)
{}

void ForceFlipEvent::execute(EngineState* const engine_state)
{
  engine_state->force(m_value);
}

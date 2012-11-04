#include "forceflipevent.h"

ForceFlipEvent::ForceFlipEvent(bool value):
  m_value (value)
{}

void ForceFlipEvent::execute(EngineState &engine_state)
{
  engine_state.force(m_value);
}

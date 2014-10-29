#include "protocols/event/forceflipevent.h"

namespace olaf
{

ForceFlipEvent::ForceFlipEvent(const bool value):
  m_value(value)
{}

void ForceFlipEvent::execute(EngineState* const engine_state)
{
  engine_state->force(m_value);

} // namespace olaf
}

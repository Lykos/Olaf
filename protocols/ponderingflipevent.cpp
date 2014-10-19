#include "ponderingflipevent.h"

namespace olaf
{

PonderingFlipEvent::PonderingFlipEvent(const bool value):
  m_value (value)
{}

void PonderingFlipEvent::execute(EngineState* const engine_state)
{
  engine_state->pondering(m_value);

} // namespace olaf
}

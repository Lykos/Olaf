#include "protocols/event/setanalyzeevent.h"

#include "protocols/enginestate.h"

namespace olaf
{

SetAnalyzeEvent::SetAnalyzeEvent(const bool value):
  m_value(value)
{}

void SetAnalyzeEvent::execute(EngineState* const engine_state)
{
  engine_state->analyze(m_value);
}

} // namespace olaf

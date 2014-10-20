#include "settimeevent.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SetTimeEvent::SetTimeEvent(const milliseconds& time):
  m_time(time)
{}

void SetTimeEvent::execute(EngineState* const engine_state)
{
  engine_state->time(m_time);

} // namespace olaf
}

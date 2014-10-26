#include "protocols/event/settimeevent.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SetTimeEvent::SetTimeEvent(const milliseconds& time, const bool my_time):
  m_time(time),
  m_my_time(my_time)
{}

void SetTimeEvent::execute(EngineState* const engine_state)
{
  if (m_my_time) {
    engine_state->my_time(m_time);
  } else {
    engine_state->opponent_time(m_time);
  }
}

} // namespace olaf


#include "settimeevent.h"

using namespace std;
using namespace chrono;

SetTimeEvent::SetTimeEvent(const milliseconds &time):
  m_time (time)
{}

void SetTimeEvent::execute(EngineState &engine_state)
{
  engine_state.time(m_time);
}

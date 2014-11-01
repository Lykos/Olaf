#include "protocols/event/setlevelevent.h"

#include "protocols/enginestate.h"

namespace olaf
{

SetLevelEvent::SetLevelEvent(const int moves_to_play,
                             const std::chrono::milliseconds& total_time,
                             const std::chrono::milliseconds& increment):
  m_moves_to_play(moves_to_play),
  m_total_time(total_time),
  m_increment(increment)
{}

void SetLevelEvent::execute(EngineState* const engine_state)
{
  engine_state->level(m_moves_to_play, m_total_time, m_increment);
}

} // namespace olaf

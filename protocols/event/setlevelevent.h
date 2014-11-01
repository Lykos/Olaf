#ifndef SETLEVELEVENT_H
#define SETLEVELEVENT_H

#include <chrono>

#include "protocols/event/engineevent.h"

namespace olaf
{

/**
 * @brief The SetLevelEvent class is an event that sets the time control.
 */
class SetLevelEvent : public EngineEvent
{
public:
  SetLevelEvent(int moves_to_play,
                const std::chrono::milliseconds& total_time,
                const std::chrono::milliseconds& increment);

  void execute(EngineState* engine_state) override;

private:
  const int m_moves_to_play;
  const std::chrono::milliseconds m_total_time;
  const std::chrono::milliseconds m_increment;
};

} // namespace olaf

#endif // SETLEVELEVENT_H

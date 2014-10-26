#ifndef SETTIMEEVENT_H
#define SETTIMEEVENT_H

#include "protocols/event/engineevent.h"
#include <chrono>

namespace olaf
{

/**
 * @brief The SetTimeEvent class represents an event that the time
 *        the engine has available has been changed.
 */
class SetTimeEvent : public EngineEvent
{
public:
  SetTimeEvent(const std::chrono::milliseconds& time, bool my_time);

  void execute(EngineState* engine_state);

private:
  const std::chrono::milliseconds m_time;

  const bool m_my_time;
};

} // namespace olaf

#endif // SETTIMEEVENT_H

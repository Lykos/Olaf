#ifndef SETTIMEEVENT_H
#define SETTIMEEVENT_H

#include "engineevent.h"
#include <chrono>

/**
 * @brief The SetTimeEvent class represents an event that the time
 *        the engine has available has been changed.
 */
class SetTimeEvent : public EngineEvent
{
public:
  SetTimeEvent(const std::chrono::milliseconds& time);

  void execute(EngineState* engine_state);

private:
  const std::chrono::milliseconds m_time;

};

#endif // SETTIMEEVENT_H

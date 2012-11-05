#ifndef SETTIMEEVENT_H
#define SETTIMEEVENT_H

#include "engineevent.h"
#include <chrono>

class SetTimeEvent : public EngineEvent
{
public:
  SetTimeEvent(const std::chrono::milliseconds &time);

  void execute(EngineState &engine_state);

private:
  std::chrono::milliseconds m_time;

};

#endif // SETTIMEEVENT_H

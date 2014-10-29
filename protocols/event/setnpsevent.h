#ifndef SETNPSEVENT_H
#define SETNPSEVENT_H

#include "protocols/event/engineevent.h"
#include <chrono>

namespace olaf
{

/**
 * @brief The SetNpsEvent class represents an event that the nps of the engine changed.
 */
class SetNpsEvent : public EngineEvent
{
public:
  SetNpsEvent(int nps);

  void execute(EngineState* engine_state);

private:
  const int m_nps;
};

} // namespace olaf

#endif // SETNPSEVENT_H

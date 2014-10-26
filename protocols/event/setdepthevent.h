#ifndef SETDEPTHEVENT_H
#define SETDEPTHEVENT_H

#include "protocols/event/engineevent.h"
#include <chrono>

namespace olaf
{

/**
 * @brief The SetDepthEvent class represents an event that the maximum
 *        depth for the engine has changed.
 */
class SetDepthEvent : public EngineEvent
{
public:
  SetDepthEvent(int depth);

  void execute(EngineState* engine_state);

private:
  const int m_depth;
};

} // namespace olaf

#endif // SETDEPTHEVENT_H

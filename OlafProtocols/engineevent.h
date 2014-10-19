#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H

#include "enginestate.h"

namespace olaf
{

/**
 * @brief The EngineEvent class is an abstract class for events sent to the engine.
 */
class EngineEvent
{
public:
  virtual void execute(EngineState* engine_state) = 0;

  virtual ~EngineEvent() = 0;
};

} // namespace olaf

#endif // ENGINEEVENT_H

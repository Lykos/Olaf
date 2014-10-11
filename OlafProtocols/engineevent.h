#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H

#include "enginestate.h"

/**
 * @brief The EngineEvent class is an abstract class for events sent to the engine.
 */
class EngineEvent
{
public:
  virtual void execute(EngineState* engine_state) = 0;

  virtual ~EngineEvent() = 0;
};

#endif // ENGINEEVENT_H

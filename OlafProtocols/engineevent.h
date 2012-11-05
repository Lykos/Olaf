#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H

#include "enginestate.h"

class EngineEvent
{
public:

  virtual void execute(EngineState& engine_state) = 0;

  virtual ~EngineEvent() = 0;

};

#endif // ENGINEEVENT_H

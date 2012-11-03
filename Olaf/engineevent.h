#ifndef ENGINEEVENT_H
#define ENGINEEVENT_H

#include "enginestate.h"

class EngineEvent
{
public:

  virtual void execute(EngineState& engine_state);

  virtual ~EngineEvent() {}

};

#endif // ENGINEEVENT_H

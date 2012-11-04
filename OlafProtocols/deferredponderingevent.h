#ifndef DEFERREDPONDERINGEVENT_H
#define DEFERREDPONDERINGEVENT_H

#include "engineevent.h"
#include "enginestate.h"

class DeferredPonderingEvent : public EngineEvent
{
public:
  void execute(EngineState &engine_state);

};

#endif // DEFERREDPONDERINGEVENT_H

#include "deferredponderingevent.h"

void DeferredPonderingEvent::execute(EngineState &engine_state)
{
  engine_state.deferred_pondering();
}

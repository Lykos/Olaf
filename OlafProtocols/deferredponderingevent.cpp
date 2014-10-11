#include "deferredponderingevent.h"

void DeferredPonderingEvent::execute(EngineState* const engine_state)
{
  engine_state->deferred_pondering();
}

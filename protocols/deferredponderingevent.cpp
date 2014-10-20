#include "deferredponderingevent.h"

namespace olaf
{

void DeferredPonderingEvent::execute(EngineState* const engine_state)
{
  engine_state->deferred_pondering();

} // namespace olaf
}

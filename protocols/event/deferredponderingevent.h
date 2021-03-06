#ifndef DEFERREDPONDERINGEVENT_H
#define DEFERREDPONDERINGEVENT_H

#include "protocols/event/engineevent.h"
#include "protocols/enginestate.h"

namespace olaf
{

/**
 * @brief The DeferredPonderingEvent class is an event that turns on pondering
 *        starting from the next turn flip, but right now turns it off. This is
 *        used at the start of a game.
 */
class DeferredPonderingEvent : public EngineEvent
{
public:
  void execute(EngineState* engine_state);

};

} // namespace olaf

#endif // DEFERREDPONDERINGEVENT_H

#ifndef FORCEFLIPEVENT_H
#define FORCEFLIPEVENT_H

#include "protocols/event/engineevent.h"
#include "protocols/enginestate.h"

namespace olaf
{

/**
 * @brief The ForceFlipEvent class that flips the "force" flag.
 */
class ForceFlipEvent : public EngineEvent
{
public:
  ForceFlipEvent(bool value);

  void execute(EngineState* engine_state);

private:
  const bool m_value;
};

} // namespace olaf

#endif // FORCEFLIPEVENT_H

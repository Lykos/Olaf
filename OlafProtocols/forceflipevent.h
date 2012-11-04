#ifndef FORCEFLIPEVENT_H
#define FORCEFLIPEVENT_H

#include "engineevent.h"
#include "enginestate.h"

class ForceFlipEvent : public EngineEvent
{
public:
  ForceFlipEvent(bool value);

  void execute(EngineState &engine_state);

private:
  bool m_value;

};

#endif // FORCEFLIPEVENT_H

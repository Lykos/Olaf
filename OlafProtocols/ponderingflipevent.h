#ifndef PONDERINGFLIP_H
#define PONDERINGFLIP_H

#include "engineevent.h"

class PonderingFlipEvent : public EngineEvent
{
public:
  PonderingFlipEvent(bool value);

  void execute(EngineState &engine_state);

private:
  bool m_value;

};

#endif // PONDERINGFLIP_H

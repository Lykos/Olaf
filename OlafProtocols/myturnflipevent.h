#ifndef MYTURNFLIP_H
#define MYTURNFLIP_H

#include "engineevent.h"

class MyTurnFlipEvent : public EngineEvent
{
public:
  MyTurnFlipEvent(bool value);

  void execute(EngineState &engine_state);

private:
  bool m_value;

};

#endif // MYTURNFLIP_H

#ifndef MYTURNFLIP_H
#define MYTURNFLIP_H

#include "engineevent.h"

/**
 * @brief The MyTurnFlipEvent class is an event that flips the boolean "my turn".
 */
class MyTurnFlipEvent : public EngineEvent
{
public:
  MyTurnFlipEvent(bool value);

  void execute(EngineState* engine_state) override;

private:
  const bool m_value;
};

#endif // MYTURNFLIP_H

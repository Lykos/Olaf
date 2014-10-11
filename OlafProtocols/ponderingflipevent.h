#ifndef PONDERINGFLIP_H
#define PONDERINGFLIP_H

#include "engineevent.h"

/**
 * @brief The PonderingFlipEvent class is an event representing a flip of the
 *        boolean that indicates whether pondering is on or off.
 */
class PonderingFlipEvent : public EngineEvent
{
public:
  PonderingFlipEvent(bool value);

  void execute(EngineState* engine_state) override;

private:
  const bool m_value;
};

#endif // PONDERINGFLIP_H

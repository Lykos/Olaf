#ifndef SETANALYZEEVENT_H
#define SETANALYZEEVENT_H

#include "protocols/event/engineevent.h"

namespace olaf
{

/**
 * @brief The SetAnalyzeEvent class is an event that turns the analysis mode on or off.
 */
class SetAnalyzeEvent : public EngineEvent
{
public:
  SetAnalyzeEvent(bool value);

  void execute(EngineState* engine_state) override;

private:
  const bool m_value;
};

} // namespace olaf

#endif // SETANALYZEEVENT_H

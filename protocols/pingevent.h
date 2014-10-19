#ifndef PINGEVENT_H
#define PINGEVENT_H

#include "engineevent.h"
#include "protocolwriter.h"
#include <memory>

namespace olaf
{

/**
 * @brief The PingEvent class is an event representing a ping from the
 */
class PingEvent : public EngineEvent
{
public:
  /**
   * @brief PingEvent does not take ownership of writer.
   */
  PingEvent(ProtocolWriter* writer, int number);

  void execute(EngineState* engine_state) override;

private:
  ProtocolWriter* const m_writer;

  const int m_number;

};

} // namespace olaf

#endif // PINGEVENT_H

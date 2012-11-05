#ifndef PINGEVENT_H
#define PINGEVENT_H

#include "engineevent.h"
#include "protocolwriter.h"
#include <memory>

class PingEvent : public EngineEvent
{
public:
  PingEvent(const std::shared_ptr<ProtocolWriter> &writer, int number);

  void execute(EngineState &engine_state);

private:
  std::shared_ptr<ProtocolWriter> m_writer;

  int m_number;

};

#endif // PINGEVENT_H

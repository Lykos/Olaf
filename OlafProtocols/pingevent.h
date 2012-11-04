#ifndef PINGEVENT_H
#define PINGEVENT_H

#include "engineevent.h"
#include "protocolwriter.h"
#include <memory>
#include <string>

class PingEvent : public EngineEvent
{
public:
  PingEvent(const std::shared_ptr<ProtocolWriter> &writer, const std::string &number);

  void execute(EngineState &engine_state);

private:
  std::shared_ptr<ProtocolWriter> m_writer;

  std::string m_number;

};

#endif // PINGEVENT_H

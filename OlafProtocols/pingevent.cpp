#include "pingevent.h"

using namespace std;

PingEvent::PingEvent(const shared_ptr<ProtocolWriter> &writer, const string &number):
  m_writer (writer),
  m_number (number)
{}

void PingEvent::execute(EngineState &engine_state)
{
  m_writer->pong(m_number);
}

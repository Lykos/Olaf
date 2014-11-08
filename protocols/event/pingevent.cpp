#include "protocols/event/pingevent.h"

using namespace std;

namespace olaf
{

PingEvent::PingEvent(ProtocolWriter* const writer, const int number):
  m_writer(writer),
  m_number(number)
{}

void PingEvent::execute(EngineState* const /* engine_state */)
{
  m_writer->pong(m_number);

} // namespace olaf
}

#include "setnpsevent.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SetNpsEvent::SetNpsEvent(const int nps):
  m_nps(nps)
{}

void SetNpsEvent::execute(EngineState* const engine_state)
{
  engine_state->use_nps(true);
  engine_state->nps(m_nps);
}

} // namespace olaf


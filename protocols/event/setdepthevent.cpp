#include "protocols/event/setdepthevent.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SetDepthEvent::SetDepthEvent(const int depth):
  m_depth(depth)
{}

void SetDepthEvent::execute(EngineState* const engine_state)
{
  engine_state->depth(m_depth);
  engine_state->use_depth(true);
}

} // namespace olaf


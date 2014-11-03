#include "setegtpathevent.h"

using namespace std;

namespace olaf
{

SetEgtPathEvent::SetEgtPathEvent(const string& path):
  m_path(path)
{}

void SetEgtPathEvent::execute(EngineState* const state)
{
  state->set_egt_path(m_path);
}

} // namespace olaf


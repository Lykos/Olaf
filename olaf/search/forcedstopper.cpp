#include "olaf/search/forcedstopper.h"

namespace olaf
{

ForcedStopper::ForcedStopper():
  m_stop(false)
{}

void ForcedStopper::request_stop()
{
  m_stop = true;
}

void ForcedStopper::reset()
{
  m_stop = false;
}

bool ForcedStopper::should_stop() const
{
  return m_stop;
}

} // namespace olaf

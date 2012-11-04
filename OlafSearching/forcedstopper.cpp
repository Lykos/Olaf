#include "forcedstopper.h"

ForcedStopper::ForcedStopper():
  m_stop (false)
{}

void ForcedStopper::request_stop()
{
  m_stop = true;
}

bool ForcedStopper::should_stop(int nodes_searched) const
{
  return m_stop;
}

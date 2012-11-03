#include "stoppablesearcher.h"

void StoppableSearcher::request_stop()
{
  m_should_stop = true;
}

bool StoppableSearcher::stop_requested() const
{
  return m_should_stop;
}

void StoppableSearcher::stopped()
{
  m_should_stop = false;
}

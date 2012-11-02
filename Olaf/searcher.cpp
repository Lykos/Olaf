#include "searcher.h"

void Searcher::request_stop()
{
  m_should_stop = true;
}

bool Searcher::should_stop() const
{
  return m_should_stop;
}

void Searcher::stopped()
{
  m_should_stop = false;
}

#include "timedsearcher.h"

using namespace std;
using namespace chrono;

TimedSearcher::~TimedSearcher() {}

void TimedSearcher::time(const milliseconds &time)
{
  m_time = time;
}

milliseconds TimedSearcher::time() const
{
  return m_time - duration_cast<milliseconds>(steady_clock::now() - m_start);
}

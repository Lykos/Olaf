#include "timestopper.h"

using namespace std;
using namespace chrono;

TimeStopper::TimeStopper(const milliseconds& millis):
  m_start(steady_clock::now()),
  m_millis(millis)
{}

bool TimeStopper::should_stop(const int /* nodes_searched */) const
{
  milliseconds elapsed = duration_cast<milliseconds>(steady_clock::now() - m_start);
  return elapsed >= m_millis;
}

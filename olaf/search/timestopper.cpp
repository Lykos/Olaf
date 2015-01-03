#include "olaf/search/timestopper.h"

using namespace std;
using namespace chrono;

namespace olaf
{

TimeStopper::TimeStopper(const steady_clock::time_point& now,
                         const milliseconds& millis):
  m_stop(now + millis)
{}

bool TimeStopper::should_stop() const
{
  return steady_clock::now() >= m_stop;
}

} // namespace olaf

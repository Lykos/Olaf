#include "olaf/search/timestopper.h"

using namespace std;
using namespace chrono;

namespace olaf
{

TimeStopper::TimeStopper(const milliseconds& millis):
  m_start(steady_clock::now()),
  m_millis(millis)
{}

bool TimeStopper::should_stop() const
{
  milliseconds elapsed = duration_cast<milliseconds>(steady_clock::now() - m_start);
  return elapsed >= m_millis;

} // namespace olaf
}

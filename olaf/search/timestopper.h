#ifndef TIMESTOPPER_H
#define TIMESTOPPER_H

#include "olaf/search/stopper.h"
#include <chrono>

namespace olaf
{

/**
 * @brief The TimeStopper class represents a class that stops the search/searching after a certain time.
 */
class TimeStopper : public Stopper
{
public:
  TimeStopper(const std::chrono::steady_clock::time_point& now,
              const std::chrono::milliseconds& millis);

  bool should_stop() const override;

private:
  const std::chrono::steady_clock::time_point m_stop;
};

} // namespace olaf

#endif // TIMESTOPPER_H

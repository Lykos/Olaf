#ifndef TIMESTOPPER_H
#define TIMESTOPPER_H

#include "stopper.h"
#include <chrono>

/**
 * @brief The TimeStopper class represents a class that stops the searching after a certain time.
 */
class TimeStopper : public Stopper
{
public:
  TimeStopper(const std::chrono::milliseconds& millis);

  bool should_stop() const override;

private:
  const std::chrono::steady_clock::time_point m_start;

  const std::chrono::milliseconds m_millis;

};

#endif // TIMESTOPPER_H

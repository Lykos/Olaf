#ifndef FORCEDSTOPPER_H
#define FORCEDSTOPPER_H

#include <atomic>

#include "olaf/search/stopper.h"

namespace olaf
{

class ForcedStopper : public Stopper
{
public:
  ForcedStopper();

  void request_stop();

  bool should_stop() const override;

private:
  std::atomic<bool> m_stop;

};

} // namespace olaf

#endif // FORCEDSTOPPER_H

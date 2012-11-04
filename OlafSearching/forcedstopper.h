#ifndef FORCEDSTOPPER_H
#define FORCEDSTOPPER_H

#include "stopper.h"
#include <atomic>

class ForcedStopper : public Stopper
{
public:
  ForcedStopper();

  void request_stop();

  bool should_stop(int nodes_searched) const;

private:
  std::atomic<bool> m_stop;

};

#endif // FORCEDSTOPPER_H

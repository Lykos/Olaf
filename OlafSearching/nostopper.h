#ifndef NOSTOPPER_H
#define NOSTOPPER_H

#include "stopper.h"

namespace olaf
{

class NoStopper : public Stopper
{
public:
  bool should_stop() const override;
};

} // namespace olaf

#endif // NOSTOPPER_H

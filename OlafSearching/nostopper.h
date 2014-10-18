#ifndef NOSTOPPER_H
#define NOSTOPPER_H

#include "stopper.h"

class NoStopper : public Stopper
{
public:
  bool should_stop() const override;
};

#endif // NOSTOPPER_H

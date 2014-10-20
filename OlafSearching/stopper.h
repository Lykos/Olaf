#ifndef STOPPER_H
#define STOPPER_H

class Stopper
{
public:
  virtual bool should_stop() const = 0;

  virtual ~Stopper();

};

#endif // STOPPER_H

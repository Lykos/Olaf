#ifndef STOPPER_H
#define STOPPER_H

class Stopper
{
public:
  virtual bool should_stop(int nodes_searched) const = 0;

  virtual ~Stopper() = 0;

};

#endif // STOPPER_H

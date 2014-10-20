#ifndef STOPPER_H
#define STOPPER_H

namespace olaf
{

class Stopper
{
public:
  virtual bool should_stop() const = 0;

  virtual ~Stopper();

};

} // namespace olaf

#endif // STOPPER_H

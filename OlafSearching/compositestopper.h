#ifndef COMPOSITESTOPPER_H
#define COMPOSITESTOPPER_H

#include "stopper.h"
#include <vector>
#include <initializer_list>
#include <memory>

class CompositeStopper : public Stopper
{
public:
  CompositeStopper(const std::vector< std::shared_ptr<Stopper> >&);

  CompositeStopper(const std::initializer_list< std::shared_ptr<Stopper> >&);

  bool should_stop(int nodes_searched) const;

private:
  std::vector< std::shared_ptr<Stopper> > m_sub_stoppers;

};

#endif // COMPOSITESTOPPER_H

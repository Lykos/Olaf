#ifndef COMPOSITESTOPPER_H
#define COMPOSITESTOPPER_H

#include "stopper.h"
#include <vector>
#include <initializer_list>
#include <boost/shared_ptr.hpp>

class CompositeStopper : public Stopper
{
public:
  CompositeStopper(const std::vector<boost::shared_ptr<Stopper>>&);

  CompositeStopper(const std::initializer_list<boost::shared_ptr<Stopper>>&);

  bool should_stop(int nodes_searched) const;

private:
  std::vector<boost::shared_ptr<Stopper>> m_sub_stoppers;

};

#endif // COMPOSITESTOPPER_H

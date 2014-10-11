#ifndef NODESTOPPER_H
#define NODESTOPPER_H

#include "stopper.h"

class NodeStopper : public Stopper
{
public:
  NodeStopper(int nodes);

  bool should_stop(int nodes_searched) const override;

private:
  int m_nodes;

};

#endif // NODESTOPPER_H

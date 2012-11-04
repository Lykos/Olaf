#include "nodestopper.h"

NodeStopper::NodeStopper(int nodes):
  m_nodes (nodes)
{}

bool NodeStopper::should_stop(int nodes_searched) const
{
  return nodes_searched > m_nodes;
}

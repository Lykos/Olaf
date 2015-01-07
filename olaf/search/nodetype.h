#ifndef NODETYPE_H
#define NODETYPE_H

#ifdef TRACE
#include <ostream>
#endif

enum class NodeType
{
  PvNode,
  CutNode,
  AllNode
};

#ifdef TRACE
std::ostream& operator <<(std::ostream& out, NodeType node_type);
#endif

#endif // NODETYPE_H

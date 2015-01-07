#include "olaf/search/nodetype.h"

using namespace std;

namespace olaf
{

#ifdef TRACE
ostream& operator <<(ostream& out, const NodeType node_type)
{
  return out << (node_type == NodeType::AllNode ? "AllNode" : (node_type == NodeType::CutNode ? "CutNode" : "PvNode"));
}
#endif

}  // namespace olaf

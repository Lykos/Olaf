#include "olaf/search/searchresult.h"

#include <limits>

using namespace std;

namespace olaf
{

static SearchResult generate_invalid()
{
  SearchResult result;
  result.valid = false;
  return result;
}

// static
const SearchResult& SearchResult::invalid()
{
  static const SearchResult c_invalid = generate_invalid();
  return c_invalid;
}

#ifdef TRACE
std::ostream& operator <<(std::ostream& out, const SearchResult& result)
{
  out << "[score=" << result.score
      << " search_depth=" << result.search_depth
      << " real_depth=" << result.real_depth
      << " terminal=" << result.terminal
      << " valid=" << result.valid
      << " node_type_valid=" << result.node_type_valid
      << " node_type=" << (result.node_type == NodeType::AllNode ? "AllNode" : (result.node_type == NodeType::CutNode ? "CutNode" : "PvNode"))
      << " main_move=";
  if (result.main_variation.empty()) {
    out << "empty ";
  } else {
    for (auto it = result.main_variation.rbegin(); it != result.main_variation.rend(); ++it)
      out << *it << " ";
  }
  return out << "]";
}
#endif

} // namespace olaf

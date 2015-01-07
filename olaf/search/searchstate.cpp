#include "olaf/search/searchstate.h"

#include <sstream>

using namespace std;

namespace olaf
{

#ifdef TRACE
ostream& operator <<(std::ostream& out, const SearchState& state)
{
  return out << "[alpha=" << state.alpha << " beta=" << state.beta << " depth=" << state.depth << "]";
}

string indentation(const SearchState& state)
{
  ostringstream oss;
  oss << "#";
  const int depth = 20 - state.depth;
  for (int i = 0; i < depth; ++i) {
    oss << " ";
  }
  return oss.str();
}
#endif

}  // namespace olaf

#include "olaf/search/searchresult.h"

#include <limits>

using namespace std;

namespace olaf
{

// static
const SearchResult& SearchResult::invalid()
{
  static const SearchResult c_invalid;
  return c_invalid;
}

// We use -max because numeric_limits is asymmetric and min
// would not work.

SearchResult::SearchResult():
  nodes(0),
  score(-numeric_limits<int>::max())
{}

bool SearchResult::valid() const
{
  return nodes > 0;

} // namespace olaf
}

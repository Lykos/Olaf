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

} // namespace olaf

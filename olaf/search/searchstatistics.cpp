#include "olaf/search/searchstatistics.h"

using namespace std;

namespace olaf
{

std::ostream& operator <<(std::ostream& out, const SearchStatistics& stats)
{
  return out << "hash move ratio: " << stats.hash_moves_at_depth_at_least_3
             << " of " << stats.sorts_at_depth_at_least_3
             << " with " << stats.entries_at_depth_at_least_3 << " candidates"
             << " of which " << stats.entries_at_depth_at_least_3_with_candidate << " have moves.";
}

} // namespace olaf


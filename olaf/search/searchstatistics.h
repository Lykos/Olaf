#ifndef SEARCHSTATISTICS_H
#define SEARCHSTATISTICS_H

#include <ostream>

namespace olaf
{

struct SearchStatistics
{
  long hash_moves_at_depth_at_least_3 = 0;
  long sorts_at_depth_at_least_3 = 0;
  long entries_at_depth_at_least_3 = 0;
  long entries_at_depth_at_least_3_with_candidate = 0;
};

std::ostream& operator <<(std::ostream& out, const SearchStatistics& stats);

} // namespace olaf

#endif // SEARCHSTATISTICS_H


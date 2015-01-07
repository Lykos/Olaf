#ifndef SEARCHSTATISTICS_H
#define SEARCHSTATISTICS_H

#include <ostream>

namespace olaf
{

struct SearchStatistics
{
  long hash_moves = 0;
  long sorts = 0;
  long retrievals_of_tt = 0;
  long hits_of_tt = 0;
  long useful_hits_of_tt = 0;
  long cutoff_by_tt = 0;
  long very_successful_null_window_searches = 0;
  long successful_null_window_searches = 0;
  long unsuccessful_null_window_searches = 0;
};

std::ostream& operator <<(std::ostream& out, const SearchStatistics& stats);

} // namespace olaf

#endif // SEARCHSTATISTICS_H


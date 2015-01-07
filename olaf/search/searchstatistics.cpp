#include "olaf/search/searchstatistics.h"

using namespace std;

namespace olaf
{

std::ostream& operator <<(std::ostream& out, const SearchStatistics& stats)
{
  return out << "hash moves: " << stats.hash_moves
             << " of " << stats.sorts
             << "; retrievals of tt: " << stats.retrievals_of_tt
             << "; successes: " << stats.hits_of_tt
             << "; useful successes: " << stats.useful_hits_of_tt
             << "; cutoffs by tt: " << stats.cutoff_by_tt
             << "; very successful null window searches: " << stats.very_successful_null_window_searches
             << "; successful null window searches: " << stats.successful_null_window_searches
             << "; unsuccessful null window searches: " << stats.unsuccessful_null_window_searches;
}

} // namespace olaf


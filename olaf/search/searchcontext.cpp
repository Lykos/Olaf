#include "olaf/search/searchcontext.h"
#include <limits>

using namespace std;

namespace olaf
{

// Note that numeric_limits is asymmetric.
// But for negamax, we need symmetry, so we use
// -max instead of min.

SearchContext::SearchContext():
  time_mode(TimeMode::BOUNDED),
  forced_stopper(nullptr),
  weak_stopper(nullptr),
  depth_mode(DepthMode::ITERATIVE)
{}

const  TranspositionTableEntry* SearchContext::get() const
{
  return transposition_table->get(board.zobrist_hash());
}

void SearchContext::put(const TranspositionTableEntry& entry)
{
  transposition_table->put(board.zobrist_hash(), entry);
}

void SearchContext::put(TranspositionTableEntry&& entry)
{
  transposition_table->put(board.zobrist_hash(), move(entry));
}

} // namespace olaf

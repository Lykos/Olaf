#include "olaf/search/searchcontext.h"
#include <limits>

using namespace std;

namespace olaf
{

SearchContext::SearchContext():
  time_mode(TimeMode::FIXED),
  total_time(0),
  forced_stopper(nullptr),
  weak_stopper(nullptr),
  depth_mode(DepthMode::ITERATIVE),
  transposition_table(nullptr)
{}

const TranspositionTableEntry* SearchContext::get() const
{
  if (transposition_table == nullptr) {
    return nullptr;
  }
  return transposition_table->get(board.zobrist_hash());
}

void SearchContext::put(const TranspositionTableEntry& entry)
{
  if (transposition_table != nullptr) {
    transposition_table->put(board.zobrist_hash(), entry);
  }
}

void SearchContext::put(TranspositionTableEntry&& entry)
{
  if (transposition_table != nullptr) {
    transposition_table->put(board.zobrist_hash(), move(entry));
  }
}

} // namespace olaf

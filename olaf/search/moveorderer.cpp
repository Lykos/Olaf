#include "olaf/search/moveorderer.h"

#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/search/searchcontext.h"

using namespace std;

namespace olaf
{

// static
void MoveOrderer::order_moves(const SearchContext& context,
                              vector<Move>* moves)
{
  const TranspositionTableEntry* const entry = context.get();
  if (entry != nullptr && entry->has_best_move) {
    for (Move& move : *moves) {
      if (move == entry->best_move) {
        swap(move, moves->front());
        break;
      }
    }
  }
}

} // namespace olaf

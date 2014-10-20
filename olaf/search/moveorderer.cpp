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
      if (move.source() == entry->best_move_source
          && move.destination() == entry->best_move_destination
          && move.is_conversion() == entry->best_move_is_conversion
          && (!move.is_conversion()
              || move.created_piece() == entry->best_move_created_piece)) {
        swap(move, moves->front());
        break;
      }
    }
  }
}

} // namespace olaf

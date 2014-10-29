#ifndef MOVEORDERER_H
#define MOVEORDERER_H

#include "olaf/rules/move.h"
#include "olaf/search/searcher.h"
#include <vector>

namespace olaf
{

class SearchContext;

/**
 * @brief The MoveOrderer class is responsible for ordering moves.
 */
class MoveOrderer
{
public:
  static Searcher::score_t see(const ChessBoard& board,
                               const Move move);

  static void order_moves(const SearchContext& context,
                          std::vector<Move>* moves);
};

} // namespace olaf

#endif // MOVEORDERER_H

#ifndef MOVEORDERER_H
#define MOVEORDERER_H

#include "olaf/rules/move.h"
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
  static void order_moves(const SearchContext& context,
                          std::vector<Move>* moves);
};

} // namespace olaf

#endif // MOVEORDERER_H

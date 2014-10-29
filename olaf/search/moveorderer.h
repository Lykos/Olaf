#ifndef MOVEORDERER_H
#define MOVEORDERER_H

#include "olaf/rules/move.h"
#include "olaf/search/searcher.h"
#include <vector>

namespace olaf
{

class Config;
class SearchContext;

/**
 * @brief The MoveOrderer class is responsible for ordering moves.
 */
class MoveOrderer
{
public:
  struct SeeState {
    BitBoard may_xray;
    BitBoard straight_pieces;
    BitBoard diagonal_pieces;
  };

  static void init_see_state(const ChessBoard& board, SeeState* see_state);

  static Searcher::score_t see(const ChessBoard& board,
                               const Move move,
                               const SeeState& see_state);

  MoveOrderer(const Config& config);

  MoveOrderer();

  void order_moves(const SearchContext& context,
                   std::vector<Move>* moves);

private:
  bool m_use_hash_move = false;
  bool m_use_see = false;
};

} // namespace olaf

#endif // MOVEORDERER_H

#ifndef MOVEORDERER_H
#define MOVEORDERER_H

#include <vector>

#include "olaf/rules/move.h"
#include "olaf/search/searcher.h"
#include "olaf/search/searchstate.h"
#include "olaf/search/searchcontext.h"
#include "olaf/config.h"

namespace olaf
{

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

  MoveOrderer(const Config::MoveOrdering& config);

  MoveOrderer();

  /**
   * @brief order_moves orders moves according to some criteria.
   * @param entry is the result from the transposition table.
   * @param state is the current search state
   * @param context is the search context
   * @param moves is the vector of moves to be ordered.
   * @return true if the first move is a hash move.
   */
  bool order_moves(const SearchResult& entry,
                   const SearchState& state,
                   SearchContext* context,
                   std::vector<Move>* moves);

private:
  bool m_use_hash_move = false;
  bool m_use_promotions = false;
  bool m_use_see = false;
  bool m_use_killers = false;
};

static_assert(SearchContext::c_no_killers < 9, "If there are 9 ore more killer, quiet moves could get below bad captures.");

} // namespace olaf

#endif // MOVEORDERER_H

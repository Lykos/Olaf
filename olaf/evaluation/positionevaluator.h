#ifndef POSITIONEVALUATOR_H
#define POSITIONEVALUATOR_H

#include <cstdint>

#include "olaf/rules/chessboard.h"
#include "olaf/search/alphabetasearcher.h"

namespace olaf
{

class ChessBoard;

class PositionEvaluator : public AlphaBetaSearcher
{
public:
  typedef std::int_fast16_t score_t;

  static const score_t c_win_score = 25000;

  static const score_t c_draw_score = 0;

  SearchResult alpha_beta(SearchState* state, SearchContext* context) final;

  virtual score_t evaluate(SearchState* state, SearchContext* context) = 0;

  virtual ~PositionEvaluator();
};

} // namespace olaf

#endif // POSITIONEVALUATOR_H

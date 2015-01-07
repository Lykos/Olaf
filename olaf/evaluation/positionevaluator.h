#ifndef POSITIONEVALUATOR_H
#define POSITIONEVALUATOR_H

#include <cstdint>

#include "olaf/search/searchresult.h"

namespace olaf
{

class ChessBoard;
class SearchState;
class SearchContext;

class PositionEvaluator
{
public:
  typedef SearchResult::score_t score_t;

  static const score_t c_win_score = 25000;

  static const score_t c_draw_score = 0;

  SearchResult alpha_beta(const SearchState& state, SearchContext* context);

  virtual score_t evaluate(const SearchState& state, SearchContext* context) = 0;

  virtual ~PositionEvaluator();
};

} // namespace olaf

#endif // POSITIONEVALUATOR_H

#ifndef QUIESCER_H
#define QUIESCER_H

#include <memory>

#include "olaf/search/searchresult.h"
#include "olaf/search/moveorderer.h"
#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class MoveGenerator;
class SearchState;

class Quiescer
{
public:
  typedef SearchResult::score_t score_t;

  Quiescer(std::unique_ptr<MoveGenerator> generator,
           MoveOrderer orderer,
           std::unique_ptr<PositionEvaluator> evaluator);

  SearchResult quiesce(const SearchState& state,
                       SearchContext* context);

private:
  std::unique_ptr<MoveGenerator> m_generator;
  MoveOrderer m_orderer;
  std::unique_ptr<PositionEvaluator> m_evaluator;
};

} // namespace olaf

#endif // QUIESCER_H

#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include <memory>

#include "olaf/search/searchresult.h"
#include "olaf/search/moveorderer.h"
#include "olaf/search/quiescer.h"

namespace olaf
{

class SearchState;
class SearchContext;
class MoveGenerator;

/**
 * @brief The NegaMaxer class is a class which implements the Negamax algorithm sequentially.
 *        It calls its sub search/searcher for the leaves.
 */
class NegaMaxer : public Searcher
{
public:
  NegaMaxer(std::unique_ptr<MoveGenerator> generator,
            const MoveOrderer& orderer,
            std::unique_ptr<Quiescer> quiescer);

  SearchResult search(SearchContext* context) override;

  SearchResult search_windowed(SearchContext* context,
                               score_t alpha,
                               score_t beta);

  SearchResult alpha_beta(const SearchState& state,
                          SearchContext* context);

private:
  std::unique_ptr<MoveGenerator> m_generator;
  MoveOrderer m_orderer;
  std::unique_ptr<Quiescer> m_quiescer;
};

} // namespace olaf

#endif // NEGAMAXER_H

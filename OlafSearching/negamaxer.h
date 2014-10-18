#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

/**
 * @brief The NegaMaxer class is a class which implements the Negamax algorithm sequentially.
 *        It calls its sub searcher for the leaves.
 */
class NegaMaxer : public AlphaBetaSearcher
{
public:
  NegaMaxer(std::unique_ptr<MoveGenerator> generator,
            std::unique_ptr<MoveOrderer> orderer,
            std::unique_ptr<AlphaBetaSearcher> sub_searcher,
            int sub_searcher_depth,
            bool ignore_depth);

  SearchResult alpha_beta(SearchState* state,
                          SearchContext* context) final;

private:
  std::unique_ptr<MoveGenerator> m_generator;

  std::unique_ptr<MoveOrderer> m_orderer;

  bool m_ignore_depth;
};

#endif // NEGAMAXER_H

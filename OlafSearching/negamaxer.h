#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

/**
 * @brief The NegaMaxer class is an abstract class which implements the Negamax algorithm.
 *        It calls its sub searcher for the leaves.
 */
class NegaMaxer : public AlphaBetaSearcher
{
public:
  NegaMaxer(const std::shared_ptr<MoveGenerator> &generator, const std::shared_ptr<MoveOrderer> &orderer, const std::shared_ptr<AlphaBetaSearcher> &searcher, bool ignore_depth);

  SearchResult search_alpha_beta(ChessBoard* board,
                                 int depth,
                                 int nodes_searched,
                                 int alpha,
                                 int beta,
                                 const Stopper& stopper) final;

private:
  std::shared_ptr<MoveGenerator> m_generator;

  std::shared_ptr<MoveOrderer> m_orderer;

  std::shared_ptr<AlphaBetaSearcher> m_searcher;

  bool m_ignore_depth;

};

#endif // NEGAMAXER_H

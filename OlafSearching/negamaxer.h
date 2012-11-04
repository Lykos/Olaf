#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

/**
 * @brief The NegaMaxer class is an abstract class which implements the Negamax algorithm, but it leaves
 * open to its subclasses when the recursion stops.
 */
class NegaMaxer : public AlphaBetaSearcher
{
public:
  NegaMaxer(const std::shared_ptr<MoveGenerator> &generator, const std::shared_ptr<MoveOrderer> &orderer, const std::shared_ptr<AlphaBetaSearcher> &searcher, bool ignore_depth);

  SearchResult search_alpha_beta(ChessBoard &board, int depth, int nodes_searched, int alpha, int beta, const std::shared_ptr<Stopper> &stopper);

private:
  std::shared_ptr<MoveGenerator> m_generator;

  std::shared_ptr<MoveOrderer> m_orderer;

  std::shared_ptr<AlphaBetaSearcher> m_searcher;

  bool m_ignore_depth;

};

#endif // NEGAMAXER_H

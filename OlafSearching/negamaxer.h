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
  NegaMaxer(std::unique_ptr<MoveGenerator> generator,
            std::unique_ptr<MoveOrderer> orderer,
            std::unique_ptr<AlphaBetaSearcher> searcher,
            bool ignore_depth);

  SearchResult search_alpha_beta(ChessBoard* board,
                                 int depth,
                                 int nodes_searched,
                                 int alpha,
                                 int beta,
                                 const Stopper& stopper) final;

private:
  std::unique_ptr<MoveGenerator> m_generator;

  std::unique_ptr<MoveOrderer> m_orderer;

  std::unique_ptr<AlphaBetaSearcher> m_searcher;

  bool m_ignore_depth;

};

#endif // NEGAMAXER_H

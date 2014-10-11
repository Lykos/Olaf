#ifndef PARALLELNEGAMAXER_H
#define PARALLELNEGAMAXER_H

#include "alphabetasearcher.h"
#include "searchresult.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include <memory>

class ParallelNegaMaxer : public AlphaBetaSearcher
{
public:
  ParallelNegaMaxer(const std::shared_ptr<MoveGenerator> &generator,
                    const std::shared_ptr<MoveOrderer> &orderer,
                    const std::shared_ptr<AlphaBetaSearcher> &searcher,
                    int sequential_depth);

  SearchResult search_alpha_beta(ChessBoard* board,
                                 int depth,
                                 int nodes_searched,
                                 int alpha,
                                 int beta,
                                 const Stopper& stopper);

private:
  std::shared_ptr<MoveGenerator> m_generator;

  std::shared_ptr<MoveOrderer> m_orderer;

  std::shared_ptr<AlphaBetaSearcher> m_searcher;

  int m_sequential_depth;

};

#endif // PARALLELNEGAMAXER_H

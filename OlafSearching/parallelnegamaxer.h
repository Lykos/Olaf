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
  ParallelNegaMaxer(std::unique_ptr<MoveGenerator> generator,
                    std::unique_ptr<MoveOrderer> orderer,
                    std::unique_ptr<AlphaBetaSearcher> searcher,
                    int sequential_depth);

  SearchResult search_alpha_beta(ChessBoard* board,
                                 int depth,
                                 int nodes_searched,
                                 int alpha,
                                 int beta,
                                 const Stopper& stopper);

private:
  std::unique_ptr<MoveGenerator> m_generator;

  std::unique_ptr<MoveOrderer> m_orderer;

  std::unique_ptr<AlphaBetaSearcher> m_searcher;

  int m_sequential_depth;

};

#endif // PARALLELNEGAMAXER_H

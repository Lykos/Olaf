#ifndef NEGAMAXER_H
#define NEGAMAXER_H

#include "searcher.h"
#include "searchresult.h"
#include "positionevaluator.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include "boost/shared_ptr.hpp"

class NegaMaxer : public Searcher
{
public:
  NegaMaxer(boost::shared_ptr<PositionEvaluator> evaluator, boost::shared_ptr<MoveOrderer> orderer);

  SearchResult search(ChessBoard &board, int depth);

private:
  static const unsigned int no_parallel_depth = 2;

  SearchResult internal_search(ChessBoard &board, int depth, int alpha, int beta);

  SearchResult no_parallel_search(ChessBoard &board, int depth, int alpha, int beta);

  boost::shared_ptr<PositionEvaluator> m_evaluator;

  boost::shared_ptr<MoveOrderer> m_orderer;

  MoveGenerator m_generator;

};

#endif // NEGAMAXER_H

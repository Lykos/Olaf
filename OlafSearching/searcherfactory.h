#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include "timedsearcher.h"
#include "iterativesearcher.h"
#include "depthsearcher.h"
#include "alphabetasearcher.h"
#include "movecreator.h"
#include "OlafEvaluation/positionevaluator.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include "OlafEvaluation/evaluatorfactory.h"
#include "thinkingwriter.h"
#include <memory>

class SearcherFactory
{
public:
  /**
   * @brief SearcherFactory does not take ownership of writer.
   */
  SearcherFactory(ThinkingWriter* writer);

  std::unique_ptr<TimedSearcher> timed_searcher() const;

  std::unique_ptr<IterativeSearcher> iterative_searcher() const;

  std::unique_ptr<DepthSearcher> parallel_depth_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> sequential_depth_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> quiescer() const;

  std::unique_ptr<AlphaBetaSearcher> evaluation_searcher() const;

  std::unique_ptr<PositionEvaluator> position_evaluator() const;

  std::unique_ptr<MoveOrderer> move_orderer() const;

  std::unique_ptr<MoveGenerator> capture_generator() const;

  std::unique_ptr<MoveGenerator> move_generator() const;

  std::unique_ptr<MoveCreator> move_creator() const;

private:
  ThinkingWriter* const m_writer;

  EvaluatorFactory m_evaluator_factory;

  static const int sequential_depth = 2;

};

#endif // ENGINEFACTORY_H

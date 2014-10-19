#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include "searcher.h"
#include "alphabetasearcher.h"
#include "movecreator.h"
#include "positionevaluator.h"
#include "movegenerator.h"
#include "moveorderer.h"
#include "evaluatorfactory.h"
#include "thinkingwriter.h"
#include "perft.h"
#include "sanparser.h"
#include "epdparser.h"
#include <memory>

namespace olaf
{

class SearcherFactory
{
public:
  /**
   * @brief SearcherFactory does not take ownership of writer.
   */
  SearcherFactory(ThinkingWriter* writer);

  std::unique_ptr<Searcher> timed_searcher() const;

  std::unique_ptr<Searcher> iterative_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> parallel_alpha_beta_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> sequential_alpha_beta_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> quiescer() const;

  std::unique_ptr<AlphaBetaSearcher> evaluation_searcher() const;

  std::unique_ptr<PositionEvaluator> position_evaluator() const;

  std::unique_ptr<MoveOrderer> move_orderer() const;

  std::unique_ptr<MoveGenerator> capture_generator() const;

  std::unique_ptr<MoveGenerator> move_generator() const;

  std::unique_ptr<MoveCreator> move_creator() const;

  std::unique_ptr<Perft> perft() const;

  std::unique_ptr<SanParser> san_parser() const;

  std::unique_ptr<EpdParser> epd_parser() const;

private:
  ThinkingWriter* const m_writer;

  EvaluatorFactory m_evaluator_factory;

  static const std::chrono::milliseconds c_search_time;

  static const int c_sequential_depth = 2;

  static const int c_min_depth = 1;

};

} // namespace olaf

#endif // ENGINEFACTORY_H

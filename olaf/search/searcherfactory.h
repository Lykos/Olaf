#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include "olaf/search/searcher.h"
#include "olaf/search/alphabetasearcher.h"
#include "olaf/evaluation/positionevaluator.h"
#include "olaf/search/movegenerator.h"
#include "olaf/evaluation/evaluatorfactory.h"
#include "olaf/search/thinkingwriter.h"
#include "olaf/search/perft.h"
#include "olaf/parse/sanparser.h"
#include "olaf/parse/epdparser.h"
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

  std::unique_ptr<MoveGenerator> capture_generator() const;

  std::unique_ptr<MoveGenerator> move_generator() const;

  std::unique_ptr<Perft> perft() const;

  std::unique_ptr<SanParser> san_parser() const;

  std::unique_ptr<EpdParser> epd_parser() const;

  std::unique_ptr<TranspositionTable> transposition_table() const;

private:
  ThinkingWriter* const m_writer;

  EvaluatorFactory m_evaluator_factory;

  static const std::chrono::milliseconds c_search_time;

  static const int c_sequential_depth = 2;

  static const int c_min_depth = 1;

  static const long c_transposition_table_size = 0x10000;

};

} // namespace olaf

#endif // ENGINEFACTORY_H

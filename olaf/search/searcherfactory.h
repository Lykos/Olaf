#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include <chrono>
#include <memory>

#include "olaf/search/searcher.h"
#include "olaf/evaluation/evaluatorfactory.h"
#include "olaf/transposition_table/transpositiontable.h"

namespace olaf
{

class AlphaBetaSearcher;
class ThinkingWriter;
class MoveGenerator;
class MoveOrderer;
class Perft;
class SanParser;
class EpdParser;

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

  static const Searcher::depth_t c_sequential_depth = 2;

  static const Searcher::depth_t c_min_depth = 1;

  static const long c_transposition_table_size = 0x10000;

};

} // namespace olaf

#endif // ENGINEFACTORY_H

#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include <chrono>
#include <memory>

#include "olaf/search/searcher.h"
#include "olaf/search/moveorderer.h"
#include "olaf/evaluation/evaluatorfactory.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/tablebases/egbbprober.h"

namespace olaf
{

class AlphaBetaSearcher;
class ThinkingWriter;
class MoveGenerator;
class MoveOrderer;
class Perft;
class SanParser;
class EpdParser;
class Config;

class SearcherFactory
{
public:
  // These can be created without config and are therefore static.
  static std::unique_ptr<MoveGenerator> capture_generator();

  static std::unique_ptr<MoveGenerator> move_generator();

  static std::unique_ptr<Perft> perft();

  static std::unique_ptr<SanParser> san_parser();

  static std::unique_ptr<EpdParser> epd_parser();

  /**
   * @brief SearcherFactory does not take ownership of writer or config.
   *        The lifetime of those objects has to be at least the lifetime of
   *        the created objects.
   */
  SearcherFactory(ThinkingWriter* writer, const Config* config);

  std::unique_ptr<Searcher> timed_searcher() const;

  std::unique_ptr<Searcher> iterative_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> parallel_alpha_beta_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> sequential_alpha_beta_searcher() const;

  std::unique_ptr<AlphaBetaSearcher> quiescer() const;

  std::unique_ptr<PositionEvaluator> evaluator() const;

  std::unique_ptr<TranspositionTable> transposition_table() const;

  std::unique_ptr<EgbbProber> egbb_prober() const;

  MoveOrderer move_orderer() const;

private:
  ThinkingWriter* const m_writer;

  EvaluatorFactory m_evaluator_factory;

  const Config* const m_config;
};

} // namespace olaf

#endif // ENGINEFACTORY_H

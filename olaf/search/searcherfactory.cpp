#include "olaf/search/searcherfactory.h"

#include "olaf/search/simpletimedsearcher.h"
#include "olaf/search/iterativedeepener.h"
#include "olaf/search/parallelnegamaxer.h"
#include "olaf/search/negamaxer.h"
#include "olaf/search/evaluatorsearcher.h"
#include "olaf/search/capturegenerator.h"
#include "olaf/search/simplemovegenerator.h"
#include "olaf/search/moveorderer.h"
#include "olaf/search/quiescer.h"
#include "olaf/search/perft.h"
#include "olaf/parse/sanparser.h"
#include "olaf/parse/epdparser.h"
#include "olaf/transposition_table/transpositiontable.h"
#include "olaf/config.h"

using namespace std;
using namespace chrono;

namespace olaf
{

SearcherFactory::SearcherFactory(ThinkingWriter* const writer,
                                 const Config* const config):
  m_writer(writer),
  m_evaluator_factory(&(config->evaluation())),
  m_config(config)
{}

unique_ptr<Searcher> SearcherFactory::timed_searcher() const
{
  unique_ptr<Searcher> searcher(new SimpleTimedSearcher(
                                  iterative_searcher(),
                                  milliseconds(m_config->search().time_millis())));
  return searcher;
}

unique_ptr<Searcher> SearcherFactory::iterative_searcher() const
{
  unique_ptr<Searcher> searcher(new IterativeDeepener(
                                  sequential_alpha_beta_searcher(),
                                  m_writer,
                                  m_config->search().min_depth()));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::parallel_alpha_beta_searcher() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new ParallelNegaMaxer(
                                           move_generator(),
                                           sequential_alpha_beta_searcher(),
                                           m_config->search().sequential_depth(),
                                           false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::sequential_alpha_beta_searcher() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new NegaMaxer(move_generator(),
                                                       quiescer(),
                                                       0,
                                                       false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::quiescer() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new Quiescer(position_evaluator(),
                                                      capture_generator(),
                                                      evaluation_searcher(),
                                                      0,
                                                      true));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::evaluation_searcher() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new EvaluatorSearcher(position_evaluator()));
  return searcher;
}

unique_ptr<PositionEvaluator> SearcherFactory::position_evaluator() const
{
  return m_evaluator_factory.evaluator();
}

unique_ptr<MoveGenerator> SearcherFactory::capture_generator() const
{
  unique_ptr<MoveGenerator> generator(new CaptureGenerator(move_generator()));
  return generator;
}

unique_ptr<MoveGenerator> SearcherFactory::move_generator() const
{
  unique_ptr<MoveGenerator> generator(new SimpleMoveGenerator);
  return generator;
}

unique_ptr<Perft> SearcherFactory::perft() const
{
  unique_ptr<Perft> perft(new Perft(move_generator()));
  return perft;
}

unique_ptr<SanParser> SearcherFactory::san_parser() const
{
  unique_ptr<SanParser> parser(new SanParser(move_generator()));
  return parser;
}

unique_ptr<EpdParser> SearcherFactory::epd_parser() const
{
  unique_ptr<EpdParser> parser(new EpdParser(san_parser()));
  return parser;
}

std::unique_ptr<TranspositionTable> SearcherFactory::transposition_table() const
{
  unique_ptr<TranspositionTable> table;
  const long size = m_config->transposition_table().size();
  if (size) {
    table.reset(new TranspositionTable(size));
  }
  return table;
}

} // namespace olaf

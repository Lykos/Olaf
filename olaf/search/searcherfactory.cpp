#include "olaf/search/searcherfactory.h"
#include "olaf/search/simpletimedsearcher.h"
#include "olaf/search/iterativedeepener.h"
#include "olaf/search/parallelnegamaxer.h"
#include "olaf/search/negamaxer.h"
#include "olaf/search/evaluatorsearcher.h"
#include "olaf/search/capturegenerator.h"
#include "olaf/search/simplemovegenerator.h"
#include "olaf/search/moveorderer.h"
#include "olaf/search/nomoveorderer.h"
#include "olaf/search/simplemovecreator.h"
#include "olaf/search/quiescer.h"

using namespace std;
using namespace chrono;

namespace olaf
{

// static
const milliseconds SearcherFactory::c_search_time(2000);

SearcherFactory::SearcherFactory(ThinkingWriter* const writer):
  m_writer(writer)
{}

unique_ptr<Searcher> SearcherFactory::timed_searcher() const
{
  unique_ptr<Searcher> searcher(new SimpleTimedSearcher(iterative_searcher(),
                                                        c_search_time));
  return searcher;
}

unique_ptr<Searcher> SearcherFactory::iterative_searcher() const
{
  unique_ptr<Searcher> searcher (new IterativeDeepener(sequential_alpha_beta_searcher(),
                                                       m_writer,
                                                       c_min_depth));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::parallel_alpha_beta_searcher() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new ParallelNegaMaxer(move_generator(),
                                                               move_orderer(),
                                                               sequential_alpha_beta_searcher(),
                                                               c_sequential_depth,
                                                               false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::sequential_alpha_beta_searcher() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new NegaMaxer(move_generator(),
                                                       move_orderer(),
                                                       quiescer(),
                                                       0,
                                                       false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::quiescer() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new Quiescer(position_evaluator(),
                                                      capture_generator(),
                                                      move_orderer(),
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

unique_ptr<MoveOrderer> SearcherFactory::move_orderer() const
{
  unique_ptr<MoveOrderer> orderer(new NoMoveOrderer());
  return orderer;
}

unique_ptr<MoveGenerator> SearcherFactory::capture_generator() const
{
  unique_ptr<MoveGenerator> generator(new CaptureGenerator(move_generator()));
  return generator;
}

unique_ptr<MoveGenerator> SearcherFactory::move_generator() const
{
  unique_ptr<MoveGenerator> generator(new SimpleMoveGenerator(move_creator()));
  return generator;
}

unique_ptr<MoveCreator> SearcherFactory::move_creator() const
{
  unique_ptr<MoveCreator> creator(new SimpleMoveCreator());
  return creator;
}

unique_ptr<Perft> SearcherFactory::perft() const
{
  unique_ptr<Perft> perft(new Perft(move_generator()));
  return perft;
}

unique_ptr<SanParser> SearcherFactory::san_parser() const
{
  unique_ptr<SanParser> parser(new SanParser(move_generator(), move_creator()));
  return parser;
}


unique_ptr<EpdParser> SearcherFactory::epd_parser() const
{
  unique_ptr<EpdParser> parser(new EpdParser(san_parser()));
  return parser;

} // namespace olaf
}

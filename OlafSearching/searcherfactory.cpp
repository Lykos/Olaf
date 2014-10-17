#include "searcherfactory.h"
#include "simpletimedsearcher.h"
#include "iterativedeepener.h"
#include "parallelnegamaxer.h"
#include "negamaxer.h"
#include "evaluatorsearcher.h"
#include "capturegenerator.h"
#include "simplemovegenerator.h"
#include "nomoveorderer.h"
#include "simplemovecreator.h"

using namespace std;
using namespace chrono;

SearcherFactory::SearcherFactory(ThinkingWriter* const writer):
  m_writer(writer)
{}

unique_ptr<Searcher> SearcherFactory::timed_searcher() const
{
  unique_ptr<Searcher> searcher(new SimpleTimedSearcher(iterative_searcher(),
                                                        milliseconds(1000)));
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
                                                       evaluation_searcher(),
                                                       0,
                                                       false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::quiescer() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new NegaMaxer(capture_generator(),
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
}

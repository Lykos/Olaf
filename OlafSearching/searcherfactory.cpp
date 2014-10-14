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

SearcherFactory::SearcherFactory(ThinkingWriter* const writer):
  m_writer(writer)
{}

unique_ptr<TimedSearcher> SearcherFactory::timed_searcher() const
{
  unique_ptr<TimedSearcher> searcher(new SimpleTimedSearcher(iterative_searcher()));
  return searcher;
}

unique_ptr<IterativeSearcher> SearcherFactory::iterative_searcher() const
{
  unique_ptr<IterativeSearcher> searcher (new IterativeDeepener(sequential_depth_searcher(), m_writer));
  return searcher;
}

unique_ptr<DepthSearcher> SearcherFactory::parallel_depth_searcher() const
{
  unique_ptr<DepthSearcher> searcher(new ParallelNegaMaxer(move_generator(), move_orderer(), sequential_depth_searcher(), sequential_depth));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::sequential_depth_searcher() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new NegaMaxer(move_generator(), move_orderer(), evaluation_searcher(), false));
  return searcher;
}

unique_ptr<AlphaBetaSearcher> SearcherFactory::quiescer() const
{
  unique_ptr<AlphaBetaSearcher> searcher(new NegaMaxer(capture_generator(), move_orderer(), evaluation_searcher(), true));
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
  unique_ptr<MoveGenerator> generator(new SimpleMoveGenerator());
  return generator;
}

unique_ptr<MoveCreator> SearcherFactory::move_creator() const
{
  unique_ptr<MoveCreator> creator(new SimpleMoveCreator());
  return creator;
}

unique_ptr<Perft> SearcherFactory::perft() const
{
  unique_ptr<Perft> perft(new Perft(move_creator(), move_generator()));
  return perft;
}

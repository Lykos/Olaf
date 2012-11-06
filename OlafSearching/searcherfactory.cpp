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

SearcherFactory::SearcherFactory(const shared_ptr<ThinkingWriter> &writer):
  m_writer (writer)
{}

shared_ptr<TimedSearcher> SearcherFactory::timed_searcher() const
{
  shared_ptr<TimedSearcher> searcher (new SimpleTimedSearcher(iterative_searcher()));
  return searcher;
}

shared_ptr<IterativeSearcher> SearcherFactory::iterative_searcher() const
{
  shared_ptr<IterativeSearcher> searcher (new IterativeDeepener(sequential_depth_searcher(), m_writer));
  return searcher;
}

shared_ptr<DepthSearcher> SearcherFactory::parallel_depth_searcher() const
{
  shared_ptr<DepthSearcher> searcher (new ParallelNegaMaxer(move_generator(), move_orderer(), sequential_depth_searcher(), sequential_depth));
  return searcher;
}

shared_ptr<AlphaBetaSearcher> SearcherFactory::sequential_depth_searcher() const
{
  shared_ptr<AlphaBetaSearcher> searcher (new NegaMaxer(move_generator(), move_orderer(), quiescer(), false));
  return searcher;
}

shared_ptr<AlphaBetaSearcher> SearcherFactory::quiescer() const
{
  shared_ptr<AlphaBetaSearcher> searcher (new NegaMaxer(capture_generator(), move_orderer(), evaluation_searcher(), true));
  return searcher;
}

shared_ptr<AlphaBetaSearcher> SearcherFactory::evaluation_searcher() const
{
  shared_ptr<AlphaBetaSearcher> searcher (new EvaluatorSearcher(position_evaluator()));
  return searcher;
}

shared_ptr<PositionEvaluator> SearcherFactory::position_evaluator() const
{
  return m_evaluator_factory.evaluator();
}

shared_ptr<MoveOrderer> SearcherFactory::move_orderer() const
{
  shared_ptr<MoveOrderer> orderer (new NoMoveOrderer());
  return orderer;
}

shared_ptr<MoveGenerator> SearcherFactory::capture_generator() const
{
  shared_ptr<MoveGenerator> generator (new CaptureGenerator(move_generator()));
  return generator;
}

shared_ptr<MoveGenerator> SearcherFactory::move_generator() const
{
  shared_ptr<MoveGenerator> generator (new SimpleMoveGenerator());
  return generator;
}

shared_ptr<MoveCreator> SearcherFactory::move_creator() const
{
  shared_ptr<MoveCreator> creator (new SimpleMoveCreator());
  return creator;
}

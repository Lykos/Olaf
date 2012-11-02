#include "enginefactory.h"
#include "negamaxer.h"
#include "materialevaluator.h"
#include "nomoveorderer.h"
#include <boost/shared_ptr.hpp>

using namespace boost;

Engine EngineFactory::create_engine(ProtocolWriter *writer) const
{
  shared_ptr<PositionEvaluator> evaluator (new MaterialEvaluator());
  shared_ptr<MoveOrderer> orderer (new NoMoveOrderer());
  shared_ptr<Searcher> searcher (new NegaMaxer(evaluator, orderer));
  return Engine(searcher, writer);
}

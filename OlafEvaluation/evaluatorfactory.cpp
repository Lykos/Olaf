#include "evaluatorfactory.h"
#include "materialevaluator.h"

using namespace std;

shared_ptr<PositionEvaluator> EvaluatorFactory::evaluator() const
{
  shared_ptr<PositionEvaluator> evaluator (new MaterialEvaluator());
  return evaluator;
}

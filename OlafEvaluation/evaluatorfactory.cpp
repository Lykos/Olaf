#include "evaluatorfactory.h"
#include "materialevaluator.h"

using namespace std;

unique_ptr<PositionEvaluator> EvaluatorFactory::evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new MaterialEvaluator());
  return evaluator;
}

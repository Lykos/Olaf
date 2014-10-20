#include "olaf/evaluation/evaluatorfactory.h"

#include "olaf/evaluation/incrementalevaluator.h"

using namespace std;

namespace olaf
{

unique_ptr<PositionEvaluator> EvaluatorFactory::evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new IncrementalEvaluator());
  return evaluator;

} // namespace olaf
}

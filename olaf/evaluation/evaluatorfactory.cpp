#include "olaf/evaluation/evaluatorfactory.h"

#include "olaf/evaluation/incrementalevaluator.h"
#include "olaf/evaluation/resultevaluator.h"
#include "olaf/evaluation/tablebaseevaluator.h"

using namespace std;

namespace olaf
{

EvaluatorFactory::EvaluatorFactory(const Config::Evaluation* const config):
  m_config(config)
{}

unique_ptr<PositionEvaluator> EvaluatorFactory::evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new ResultEvaluator(tablebase_evaluator()));
  return evaluator;
}

unique_ptr<PositionEvaluator> EvaluatorFactory::tablebase_evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new TablebaseEvaluator(incremental_evaluator()));
  return evaluator;
}

unique_ptr<PositionEvaluator> EvaluatorFactory::incremental_evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new IncrementalEvaluator());
  return evaluator;
}

} // namespace olaf

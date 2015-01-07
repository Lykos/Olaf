#include "olaf/evaluation/evaluatorfactory.h"

#include "olaf/evaluation/incrementalevaluator.h"
#include "olaf/evaluation/resultevaluator.h"
#include "olaf/evaluation/tablebaseevaluator.h"
#include "olaf/evaluation/compositeevaluator.h"
#include "olaf/evaluation/kingsafetyevaluator.h"
#include "olaf/evaluation/pawnevaluator.h"

using namespace std;

namespace olaf
{

EvaluatorFactory::EvaluatorFactory(const Config::Evaluation* const config):
  m_config(config)
{}

unique_ptr<PositionEvaluator> EvaluatorFactory::evaluator() const
{
  vector<std::unique_ptr<PositionEvaluator>> sub_evaluators;
  //sub_evaluators.emplace_back(tablebase_evaluator());
  sub_evaluators.emplace_back(incremental_evaluator());
  sub_evaluators.emplace_back(kingsafety_evaluator());
  std::unique_ptr<PositionEvaluator> composite_evaluator(
        new CompositeEvaluator(std::move(sub_evaluators)));
  unique_ptr<PositionEvaluator> evaluator(new ResultEvaluator(std::move(composite_evaluator)));
  return evaluator;
}

unique_ptr<PositionEvaluator> EvaluatorFactory::tablebase_evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new TablebaseEvaluator());
  return evaluator;
}

unique_ptr<PositionEvaluator> EvaluatorFactory::incremental_evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new IncrementalEvaluator());
  return evaluator;
}

unique_ptr<PositionEvaluator> EvaluatorFactory::kingsafety_evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new KingSafetyEvaluator());
  return evaluator;
}

unique_ptr<PositionEvaluator> EvaluatorFactory::pawn_evaluator() const
{
  unique_ptr<PositionEvaluator> evaluator(new PawnEvaluator());
  return evaluator;
}

} // namespace olaf

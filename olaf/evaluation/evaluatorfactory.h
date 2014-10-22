#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include <memory>
#include "olaf/evaluation/positionevaluator.h"

namespace olaf
{

class EvaluatorFactory
{
public:
  std::unique_ptr<PositionEvaluator> evaluator() const;

  std::unique_ptr<PositionEvaluator> incremental_evaluator() const;

};

} // namespace olaf

#endif // EVALUATORFACTORY_H

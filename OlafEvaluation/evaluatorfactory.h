#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include <memory>
#include "positionevaluator.h"

class EvaluatorFactory
{
public:
  std::shared_ptr<PositionEvaluator> evaluator() const;

};

#endif // EVALUATORFACTORY_H

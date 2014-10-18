#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include <memory>
#include "positionevaluator.h"

class EvaluatorFactory
{
public:
  std::unique_ptr<PositionEvaluator> evaluator() const;

};

#endif // EVALUATORFACTORY_H

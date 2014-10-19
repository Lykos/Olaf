#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include <memory>
#include "positionevaluator.h"

namespace olaf
{

class EvaluatorFactory
{
public:
  std::unique_ptr<PositionEvaluator> evaluator() const;

};

} // namespace olaf

#endif // EVALUATORFACTORY_H

#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include <memory>

namespace olaf
{

class PositionEvaluator;

class EvaluatorFactory
{
public:
  std::unique_ptr<PositionEvaluator> evaluator() const;

  std::unique_ptr<PositionEvaluator> incremental_evaluator() const;

};

} // namespace olaf

#endif // EVALUATORFACTORY_H

#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include <memory>

#include "olaf/config.h"

namespace olaf
{

class PositionEvaluator;

class EvaluatorFactory
{
public:
  explicit EvaluatorFactory(const Config::Evaluation* const config);

  std::unique_ptr<PositionEvaluator> evaluator() const;

  std::unique_ptr<PositionEvaluator> incremental_evaluator() const;

private:
  const Config::Evaluation* const m_config;
};

} // namespace olaf

#endif // EVALUATORFACTORY_H

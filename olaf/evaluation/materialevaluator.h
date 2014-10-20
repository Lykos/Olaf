#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include "olaf/evaluation/positionevaluator.h"
#include "olaf/rules/chessboard.h"
#include <vector>

namespace olaf
{

class MaterialEvaluator : public PositionEvaluator
{
public:
  MaterialEvaluator();

  score_t evaluate(const ChessBoard& board) override;

private:
  std::vector<int> m_piece_values;

};

} // namespace olaf

#endif // MATERIALEVALUATOR_H

#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include "positionevaluator.h"
#include "chessboard.h"
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

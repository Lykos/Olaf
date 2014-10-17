#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include "positionevaluator.h"
#include "chessboard.h"
#include <vector>

class MaterialEvaluator : public PositionEvaluator {
public:
  MaterialEvaluator();

  score_t evaluate(const ChessBoard& board) override;

private:
  std::vector<int> m_piece_values;

};

#endif // MATERIALEVALUATOR_H

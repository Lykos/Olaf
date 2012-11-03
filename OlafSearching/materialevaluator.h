#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include "positionevaluator.h"
#include <vector>

class MaterialEvaluator : public PositionEvaluator {
public:
  MaterialEvaluator();

  int evaluate(const ChessBoard &board);

private:
  std::vector<int> m_piece_values;

};

#endif // MATERIALEVALUATOR_H

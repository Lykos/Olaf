#include "olaf/evaluation/incrementalevaluator.h"

#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"

namespace olaf
{

IncrementalEvaluator::score_t IncrementalEvaluator::evaluate(const ChessBoard& board)
{
  return board.incremental_score();
}

} // namespace olaf

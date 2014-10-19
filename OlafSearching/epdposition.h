#ifndef EPDPOSITION_H
#define EPDPOSITION_H

#include <string>
#include <vector>

#include "chessboard.h"
#include "move.h"

namespace olaf
{

struct EpdPosition
{
  ChessBoard board;
  std::vector<Move> avoid_moves;
  std::vector<Move> best_moves;
  std::string id;
};

} // namespace olaf

#endif // EPDPOSITION_H

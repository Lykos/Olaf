#ifndef EPDPOSITION_H
#define EPDPOSITION_H

#include <string>
#include <vector>

#include "OlafRules/chessboard.h"
#include "OlafRules/move.h"

struct EpdPosition
{
  ChessBoard board;
  std::vector<Move> avoid_moves;
  std::vector<Move> best_moves;
  std::string id;
};

#endif // EPDPOSITION_H

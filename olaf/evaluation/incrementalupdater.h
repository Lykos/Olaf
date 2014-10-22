#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include <vector>

#include "olaf/rules/piece.h"

namespace olaf
{

class Position;
class ChessBoard;

class IncrementalUpdater
{
public:
  static void calculate(ChessBoard* board);

  static void remove_piece(Color color,
                           Piece::piece_index_t piece_index,
                           const Position& position,
                           ChessBoard* board);

  static void add_piece(Color color,
                        Piece::piece_index_t piece_index,
                        const Position& position,
                        ChessBoard* board);
};

} // namespace olaf

#endif // MATERIALEVALUATOR_H

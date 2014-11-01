#ifndef MATERIALEVALUATOR_H
#define MATERIALEVALUATOR_H

#include <array>

#include "olaf/rules/piece.h"
#include "olaf/rules/pieceset.h"

namespace olaf
{

class Position;
class ChessBoard;

class IncrementalUpdater
{
public:
  static void calculate(ChessBoard* board);

  static std::array<int, PieceSet::c_no_pieces> piece_values();

  static void remove_piece(Color color,
                           Piece::piece_index_t piece_index,
                           Position position,
                           ChessBoard* board);

  static void add_piece(Color color,
                        Piece::piece_index_t piece_index,
                        Position position,
                        ChessBoard* board);
};

} // namespace olaf

#endif // MATERIALEVALUATOR_H

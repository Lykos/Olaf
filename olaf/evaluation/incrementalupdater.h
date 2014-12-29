#ifndef INCREMENTALUPDATER_H
#define INCREMENTALUPDATER_H

#include <array>

#include "olaf/rules/piece.h"
#include "olaf/rules/pieceset.h"
#include "olaf/search/searchresult.h"

namespace olaf
{

class Position;
class ChessBoard;
class IncrementalState;

class IncrementalUpdater
{
public:
  typedef SearchResult::score_t score_t;

  static score_t weighted_score(score_t middlegame_score,
                                score_t endgame_score,
                                score_t total_material_score);

  static void calculate(const ChessBoard& board, IncrementalState* state);

  static std::array<score_t, PieceSet::c_no_pieces> piece_values();

  static void remove_piece(Color color,
                           Piece::piece_index_t piece_index,
                           Position position,
                           IncrementalState* state);

  static void add_piece(Color color,
                        Piece::piece_index_t piece_index,
                        Position position,
                        IncrementalState* state);
};

} // namespace olaf

#endif // INCREMENTALUPDATER_H

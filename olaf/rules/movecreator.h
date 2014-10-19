#ifndef MOVECREATOR_H
#define MOVECREATOR_H

#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/move.h"
#include "olaf/rules/piece.h"

namespace olaf
{

/**
 * @brief The MoveCreator class is responsible for checking moves from the user and
 * creating the move objects.
 */
class MoveCreator
{
public:
  static bool valid_move(const ChessBoard& board,
                         const Position& source,
                         const Position& destination);

  static bool valid_move(const ChessBoard& board,
                         const Position& source,
                         const Position& destination,
                         Piece::piece_index_t conversion);

  static bool pseudo_valid_move(const ChessBoard& board,
                                const Position& source,
                                const Position& destination);

  static bool pseudo_valid_move(const ChessBoard& board,
                                const Position& source,
                                const Position& destination,
                                Piece::piece_index_t conversion);

  static Move create_move(const ChessBoard& board,
                          const Position& source,
                          const Position& destination);

  static Move create_move(const ChessBoard& board,
                          const Position& source,
                          const Position& destination,
                          Piece::piece_index_t conversion);

private:
  static bool is_killable(const ChessBoard& board);
};

} // namespace olaf

#endif // MOVECREATOR_H

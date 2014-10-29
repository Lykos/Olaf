#ifndef MOVECREATOR_H
#define MOVECREATOR_H

#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/move.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/color.h"

namespace olaf
{

/**
 * @brief The MoveCreator class is responsible for checking moves from the user and
 * creating the move objects.
 */
class MoveChecker
{
public:
  /**
   * @brief valid_move checks whether the move is valid on the given board. This does not
   *        allow the piece to go into check.
   */
  static bool valid_move(const ChessBoard& board,
                         IncompleteMove incomplete_move);

  /**
   * @brief pseudo_valid_move checks whether the move is pseudo valid on the given board.
   *        This checks only whether the piece can perform the move, but not whether the
   *        king is left in check.
   */
  static bool pseudo_valid_move(const ChessBoard& board,
                                IncompleteMove incomplete_move);

  /**
   * @brief complete creates a new move for which the flags are set correctly.
   */
  static Move complete(IncompleteMove incomplete_move,
                       const ChessBoard& board);
  inline static Move complete(const Position& source,
                              const Position& destination,
                              const ChessBoard& board)
  {
    return complete(IncompleteMove(source, destination), board);
  }
  inline static Move complete_promotion(const Position& source,
                                        const Position& destination,
                                        const Piece::piece_index_t created_piece,
                                        const ChessBoard& board)
  {
    return complete(IncompleteMove::promotion(source, destination, created_piece), board);
  }

  /**
   * @brief is_in_check returns true if the side to move can kill the opposing king.
   */
  static bool can_kill_king(const ChessBoard& board);
};

} // namespace olaf

#endif // MOVECREATOR_H

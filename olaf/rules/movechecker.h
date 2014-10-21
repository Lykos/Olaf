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
class MoveChecker
{
public:
  static bool valid_move(const ChessBoard& board,
                         IncompleteMove incomplete_move);

  static bool pseudo_valid_move(const ChessBoard& board,
                                IncompleteMove incomplete_move);

private:
  static bool is_killable(const ChessBoard& board);
};

} // namespace olaf

#endif // MOVECREATOR_H

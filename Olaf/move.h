#ifndef MOVE_H
#define MOVE_H

#include <boost/shared_ptr.hpp>

class MoveAction;

class ChessBoard;

/**
 * @brief The Move class represents a move that encapsulates a possible move action
 */
class Move
{
public:
  Move(MoveAction* move_action);

  /**
   * @brief execute executes the move action and flips the turn color.
   */
  void execute(ChessBoard&);

  /**
   * @brief undo takes back the move action and flips the turn color.
   */
  void undo(ChessBoard&);

private:
  boost::shared_ptr<MoveAction> m_move_ptr;

};

#include "chessboard.h"
#include "moveaction.h"

#endif // MOVE_H

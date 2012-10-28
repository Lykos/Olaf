#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include <cassert>
#include "chessboard.h"

/**
 * @brief The Move class represents a move that can be executed or undone.
 */
class Move
{
public:
  Move();

  /**
   * @brief execute executes the move on the given chessboard. Can not be called if the move has already been
   * executed and not undone.
   * @param ChessBoard is the board on which it should be executed.
   */
  execute(ChessBoard);

  /**
   * @brief undo
   */
  undo();

private:
  Position m_ep_field;

  ChessBoard* m_chess_board;

  bool m_executed;

  vector<bool> taken;

};

#endif // MOVE_H

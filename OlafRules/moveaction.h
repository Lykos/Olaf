#ifndef MOVEACTION_H
#define MOVEACTION_H

class ChessBoard;

/**
 * @brief The MoveAction class is an abstract class that represents a move that can be executed or undone.
 */
class MoveAction
{
public:

  /**
   * @attention Should not be called if the move has already been executed and not undone and the behaviour
   * is undefined if there is no piece of the color whose turn it is.
   * @brief execute executes the move on the given chessboard.
   * @param chess_board is the board on which it should be executed.
   */
  virtual void execute(ChessBoard* chess_board) = 0;

  /**
   * Takes back the move. Should only be called if this was the last executed move on this particular chess board.
   * @param chess_board the chessboard on which it should be undone.
   * @brief undo takes back the move.
   */
  virtual void undo(ChessBoard* chess_board) = 0;

  virtual ~MoveAction() {}

};

#include "chessboard.h"

#endif // MOVEACTION_H

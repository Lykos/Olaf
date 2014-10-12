#ifndef MOVEACTION_H
#define MOVEACTION_H

#include <memory>
#include <vector>

class ChessBoard;

/**
 * @brief The MoveAction class is an abstract class that represents a move that can be executed or undone.
 */
class MoveAction
{
public:

  /**
   * @attention Should not be called if the move has already been executed and not undone and the behaviour
   *            is undefined if there is no piece of the color whose turn it is.
   * @brief execute executes the move on the given chessboard.
   * @param chess_board is the board on which it should be executed.
   */
  virtual void execute(ChessBoard* chess_board) = 0;

  /**
   * Takes back the move. Should only be called if this was the last executed move on this particular chess board.
   * @brief undo takes back the move.
   * @param chess_board the chessboard on which it should be undone.
   */
  virtual void undo(ChessBoard* chess_board) = 0;

  /**
   * @brief priority returns the priority of the move action. This is used for the order of their execution.
   */
  virtual int priority() const = 0;

  /**
   * @brief copy returns a copy of the move action.
   */
  virtual std::unique_ptr<MoveAction> copy() const = 0;

  virtual ~MoveAction() {}

  static const int CAPTURE_ACTION_PRIORITY = 1;
  static const int PIECE_MOVE_ACTION_PRIORITY = 2;
  static const int CONVERSION_ACTION_PRIORITY = 3;
  static const int EP_DISABLE_PRIORITY = 4;
  static const int EP_ENABLE_PRIORITY = 5;
  static const int ANTI_CASTLE_ACTION_PRIORITY = 6;
  static const int TURN_FLIP_ACTION_PRIORITY = 7;
};

typedef std::vector<std::unique_ptr<MoveAction>> MoveActions;

#include "chessboard.h"

#endif // MOVEACTION_H

#ifndef PAWNDOUBLEMOVE_H
#define PAWNDOUBLEMOVE_H

#include "simplemoveaction.h"
#include "colorboard.h"
#include "moveaction.h"
#include "position.h"

class ChessBoard;

/**
 * @brief The PawnDoubleMove class represents a pawn double move which enables ep.
 */
class PawnDoubleMove : public MoveAction
{
public:
  /**
   * @brief PawnDoubleMove
   * @param source
   * @param destination
   * @param new_ep_capture_position
   * @param new_ep_victim_position
   */
  PawnDoubleMove(ColorBoard::piece_index_t, Position source, Position destination, Position new_ep_capture_position, Position new_ep_victim_position);

  void execute(ChessBoard& chess_board);

  void undo(ChessBoard& chess_board);

private:
  SimpleMoveAction m_simple_move;

  Position m_old_ep_capture_position;

  Position m_old_ep_victim_position;

  Position m_new_ep_capture_position;

  Position m_new_ep_victim_position;

};

#include "chessboard.h"

#endif // PAWNDOUBLEMOVE_H

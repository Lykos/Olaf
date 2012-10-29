#ifndef SIMPLEMOVEACTION_H
#define SIMPLEMOVEACTION_H

#include "position.h"
#include "moveaction.h"
#include "colorboard.h"
#include <cassert>

class ChessBoard;

/**
 * @brief The SimpleMoveAction class represents a move that can be executed or undone.
 */
class SimpleMoveAction : public MoveAction
{
public:
  /**
   * @brief Move creates a move that moves from source to destination
   * @param piece_index is the index of the piece to be moved.
   * @param source is the source position
   * @param destination is the destination position
   */
  SimpleMoveAction(ColorBoard::piece_index_t piece_index, const Position& source, const Position& destination);

  void execute(ChessBoard& chess_board);

  void undo(ChessBoard& chess_board);

private:
  ColorBoard::piece_index_t m_piece_index;

  Position m_source;

  Position m_destination;

  bool m_old_ep_possible;

  bool m_capture;

  Position m_victim_position;

  ColorBoard::piece_index_t m_victim_index;

};

#include "chessboard.h"

#endif // SIMPLEMOVEACTION_H

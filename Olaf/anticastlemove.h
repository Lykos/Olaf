#ifndef ANTICASTLEMOVE_H
#define ANTICASTLEMOVE_H

#include "moveaction.h"
#include "simplemoveaction.h"
#include "colorboard.h"

class ChessBoard;

/**
 * @brief The AntiCastleMove class represents a move that changes the castling rights
 */
class AntiCastleMove : public MoveAction
{
public:
  /**
   * @brief AntiCastleMove
   * @param piece_index
   * @param source
   * @param destination
   * @param new_can_castle_q
   * @param new_can_castle_k
   */
  AntiCastleMove(ColorBoard::piece_index_t piece_index, const Position& source, const Position& destination, bool new_can_castle_q, bool new_can_castle_k);

  void execute(ChessBoard &chess_board);

  void undo(ChessBoard &chess_board);

private:
  SimpleMoveAction m_simple_move;

  bool m_old_can_castle_q;

  bool m_old_can_castle_k;

  bool m_new_can_castle_q;

  bool m_new_can_castle_k;

};

#include "chessboard.h"

#endif // ANTICASTLEMOVE_H

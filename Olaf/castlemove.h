#ifndef CASTLEMOVE_H
#define CASTLEMOVE_H

#include "moveaction.h"
#include "simplemoveaction.h"
#include "chessboard.h"

/**
 * @brief The CastleMove class represents a castling move represented by two submoves.
 */
class CastleMove : public MoveAction
{
public:
  /**
   * @brief CastleMove
   * @param king_move
   * @param rook_move
   */
  CastleMove(const SimpleMoveAction &king_move, const SimpleMoveAction &rook_move);

  void execute(ChessBoard &chess_board);

  void undo(ChessBoard &chess_board);

private:
  SimpleMoveAction m_king_move;

  SimpleMoveAction m_rook_move;

  bool m_old_can_castle_q;

  bool m_old_can_castle_k;

};

#endif // CASTLEMOVE_H

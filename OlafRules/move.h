#ifndef MOVE_H
#define MOVE_H

#include <memory>
#include <vector>

#include "piece.h"
#include "moveaction.h"

class Move
{
 public:
  /**
   * @brief Move consumes move_actions.
   */
  Move(MoveActions&& move_actions,
       const Position& source,
       const Position& destination,
       bool capture,
       bool conversion,
       Piece::piece_index_t created_piece);

  Move(const Move& move);

  Move(Move&& move);

  ~Move();

  /**
   * @brief execute executes the moves.
   */
  void execute(ChessBoard* chessboard);

  /**
   * @brief undo takes back the move actions.
   */
  void undo(ChessBoard* chessboard);

  const Position& source() const;

  const Position& destination() const;

  bool is_capture() const;

  bool is_conversion() const;

  Piece::piece_index_t created_piece() const;

private:
  MoveActions m_move_actions;

  const Position m_source;

  const Position m_destination;

  const bool m_conversion;

  const bool m_capture;

  const Piece::piece_index_t m_created_piece;
};

#include "moveaction.h"

#endif // MOVE_H

#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "position.h"
#include "pieceset.h"
#include "colorboard.h"

class MoveAction;
class ChessBoard;

/**
 * @brief The Move class represents a move that encapsulates a possible move action
 */
class Move
{
public:
  /**
   * @brief Move creates a default move that moves a piece and flips the turn but does
   * nothing else (capturing etc is not handled).
   * @param piece_index
   * @param source
   * @param destination
   */
  Move(PieceSet::piece_index_t piece_index, const Position& source, const Position& destination);

  /**
   * @brief move_piece moves an additional piece.
   * @param piece_index
   * @param source
   * @param destination
   */
  void move_piece(PieceSet::piece_index_t piece_index, const Position& source, const Position& destination);

  /**
   * @brief disable_ep enables en passent capturing after this move.
   * @param capture_position
   * @param victim_position
   */
  void enable_ep(const Position& capture_position, const Position& victim_position);

  /**
   * @brief disable_ep disables en passent capturing after this move.
   */
  void disable_ep();

  /**
   * @brief capture adds the capturing action to this move.
   * @param piece_index
   * @param victim_position
   */
  void capture(PieceSet::piece_index_t piece_index, const Position& victim_position);

  void forbid_castling();

  void forbid_q_castling();

  void forbid_k_castling();

  /**
   * @brief conversion
   * @param position
   * @param removed_piece
   * @param created_piece
   */
  void conversion(const Position &position, PieceSet::piece_index_t removed_piece, PieceSet::piece_index_t created_piece);

  /**
   * @brief execute executes the move action and flips the turn color.
   */
  void execute(ChessBoard&);

  /**
   * @brief undo takes back the move action and flips the turn color.
   */
  void undo(ChessBoard&);

  ~Move();

private:
  std::vector<MoveAction*> m_move_ptrs;

};

#include "chessboard.h"
#include "moveaction.h"

#endif // MOVE_H

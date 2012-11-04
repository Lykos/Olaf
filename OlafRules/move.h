#ifndef MOVE_H
#define MOVE_H

#include "position.h"
#include "pieceset.h"
#include "colorboard.h"
#include <memory>
#include <vector>

class MoveAction;
class ChessBoard;

/**
 * @brief The Move class represents a move that encapsulates a possible move action
 */
class Move
{
public:
  /**
   * @brief Move creates an empty move that does nothing. Not even the turn flip.
   */
  Move();

  /**
   * @brief Move creates a default move that moves a piece, disables ep and handles normal capturing (but not ep capturing) and turn flip.
   * @param board
   * @param piece_index
   * @param source
   * @param destination
   */
  Move(const ChessBoard &board, Piece::piece_index_t piece_index, const Position &source, const Position &destination);

  /**
   * @brief Move creates a default move that moves a piece, enables ep at the given position and handles normal capturing (but not ep capturing) and turn flip.
   * @param board
   * @param piece_index
   * @param source
   * @param destination
   * @param capture_position Position at which an ep capture can be performed
   */
  Move(const ChessBoard &board, Piece::piece_index_t piece_index, const Position &source, const Position &destination, const Position &capture_position);

  /**
   * @brief Move creates a castling move that moves king and rook, disables ep and handles turn flip.
   * @param board
   * @param source
   * @param destination
   */
  Move(const ChessBoard &board, const Position &source, const Position &destination);

  void capture_ep(const ChessBoard &board);

  void forbid_castling();

  void forbid_q_castling();

  void forbid_k_castling();

  /**
   * @brief conversion
   * @param position
   * @param removed_piece
   * @param created_piece
   */
  void conversion(const Position &position, Piece::piece_index_t removed_piece, Piece::piece_index_t created_piece);

  /**
   * @brief execute executes the move action and flips the turn color.
   */
  void execute(ChessBoard&);

  /**
   * @brief undo takes back the move action and flips the turn color.
   */
  void undo(ChessBoard&);

  const Position& source() const;

  const Position& destination() const;

  bool is_capture() const;

  bool is_conversion() const;

  Piece::piece_index_t created_piece() const;

private:
  std::vector< std::shared_ptr<MoveAction> > m_move_actions;

  Position m_source;

  Position m_destination;

  bool m_conversion = false;

  bool m_capture = false;

  bool m_created_piece;

};

#include "chessboard.h"
#include "moveaction.h"

#endif // MOVE_H

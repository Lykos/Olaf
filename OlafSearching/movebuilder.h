#ifndef MOVEBUILDER_H
#define MOVEBUILDER_H

#include <memory>
#include <vector>

#include "position.h"
#include "pieceset.h"
#include "colorboard.h"
#include "move.h"

class MoveAction;
class ChessBoard;

/**
 * @brief The MoveBuilder class is used to build a move.
 */
class MoveBuilder
{
public:
  static Move castle(const ChessBoard& board,
                     const Position& source,
                     const Position& destination);

  /**
   * @brief Move creates a default move that moves a piece, disables ep and
   *        handles normal capturing (but not ep capturing) and turn flip.
   * @param board
   * @param source
   * @param destination
   */
  MoveBuilder(const ChessBoard& board,
              const Position& source,
              const Position& destination);

  MoveBuilder(const MoveBuilder& builder);

  MoveBuilder(MoveBuilder&& builder);

  ~MoveBuilder();

  void enable_ep(const Position& capture_position);

  void capture_ep(const ChessBoard& board);

  void forbid_castling();

  void forbid_q_castling();

  void forbid_k_castling();

  /**
   * @brief conversion
   * @param position
   * @param removed_piece
   * @param created_piece
   */
  void conversion(const Position& position,
                  Piece::piece_index_t removed_piece,
                  Piece::piece_index_t created_piece);

  /**
   * @brief build creates a move.
   */
  Move build();

private:
  MoveActions copy_move_actions() const;

  MoveActions m_move_actions;

  const Position m_source;

  const Position m_destination;

  bool m_conversion = false;

  bool m_capture = false;

  Piece::piece_index_t m_created_piece = Piece::c_no_piece;
};

#include "chessboard.h"
#include "moveaction.h"

#endif // MOVEBUILDER_H

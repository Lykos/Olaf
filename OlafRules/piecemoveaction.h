#ifndef PIECEMOVEACTION_H
#define PIECEMOVEACTION_H

#include <memory>

#include "position.h"
#include "moveaction.h"
#include "colorboard.h"
#include "pieceset.h"

class ChessBoard;

/**
 * @brief The PieceMoveAction class represents the actual piece movement.
 */
class PieceMoveAction : public MoveAction
{
public:
  /**
   * @brief Move creates a move that moves from source to destination
   * @param piece_index is the index of the piece to be moved.
   * @param source is the source position
   * @param destination is the destination position
   */
  PieceMoveAction(PieceSet::piece_index_t piece_index,
                  const Position& source,
                  const Position& destination);

  void execute(ChessBoard* chess_board) override;

  void undo(ChessBoard* chess_board) override;

  std::unique_ptr<MoveAction> copy() const override;

  int priority() const override;

private:
  const PieceSet::piece_index_t m_piece_index;

  const Position m_source;

  const Position m_destination;
};

#include "chessboard.h"

#endif // PIECEMOVEACTION_H

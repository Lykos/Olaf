#ifndef PIECEBOARD_H
#define PIECEBOARD_H

#include "bitboard.h"
#include "piece.h"
#include "position.h"
#include "color.h"
#include <memory>

/**
 * @brief The PieceBoard class represents a bitboard associated with a given pieceboard.
 */
class PieceBoard
{
public:
  /**
   * @brief PieceBoard does not take ownership of piece.
   */
  PieceBoard(const Piece* piece, const BitBoard& bit_board);

  operator BitBoard() const;

  const Piece& piece() const;

  bool get(const Position& position) const;

  void set(const Position& position, bool value);

  const BitBoard& bit_board() const;

private:
  const Piece* const m_piece;

  BitBoard m_bit_board;

};

#endif // PIECEBOARD_H

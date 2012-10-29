#ifndef PIECEBOARD_H
#define PIECEBOARD_H

#include "bitboard.h"
#include "piece.h"
#include "position.h"
#include "color.h"

/**
 * @brief The PieceBoard class represents a bitboard associated with a given pieceboard.
 */
class PieceBoard
{
public:
  PieceBoard(const Piece&, BitBoard);

  operator BitBoard() const;

  const Piece& piece() const;

  bool get(Position);

  void set(Position, bool);

private:
  Color m_color;

  const Piece &m_piece;

  BitBoard m_bit_board;

};

#endif // PIECEBOARD_H

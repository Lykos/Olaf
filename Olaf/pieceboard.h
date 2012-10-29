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
  PieceBoard(const Piece*, const BitBoard&);

  operator BitBoard() const;

  const Piece &piece() const;

  bool get(const Position&) const;

  void set(const Position&, bool);

private:
  const Piece *m_piece;

  BitBoard m_bit_board;

};

#endif // PIECEBOARD_H

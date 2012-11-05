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
  PieceBoard(const std::shared_ptr<const Piece>&, const BitBoard&);

  operator BitBoard() const;

  const std::shared_ptr<const Piece>& piece() const;

  bool get(const Position&) const;

  void set(const Position&, bool);

  const BitBoard& bit_board() const;

private:
  std::shared_ptr<const Piece> m_piece;

  BitBoard m_bit_board;

};

#endif // PIECEBOARD_H

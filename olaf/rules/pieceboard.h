#ifndef PIECEBOARD_H
#define PIECEBOARD_H

#include <memory>
#include <vector>

#include "olaf/rules/bitboard.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"
#include "color.h"

namespace olaf
{

class PieceBoard;

bool operator ==(const PieceBoard& left, const PieceBoard& right);

/**
 * @brief The PieceBoard class represents a bitboard associated with a given pieceboard.
 */
class PieceBoard
{
  friend bool operator ==(const PieceBoard& left, const PieceBoard& right);

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

  std::vector<Position> positions() const;

private:
  const Piece* m_piece;

  BitBoard m_bit_board;
};

} // namespace olaf

#endif // PIECEBOARD_H

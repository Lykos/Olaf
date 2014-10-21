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
  constexpr PieceBoard(const Piece* piece = nullptr, const BitBoard bit_board = BitBoard(0)):
    m_piece(piece),
    m_bit_board(bit_board)
  {}

  constexpr operator BitBoard() const
  {
    return m_bit_board;
  }

  constexpr const Piece& piece() const
  {
    return *m_piece;
  }

  constexpr bool get(const Position& position) const
  {
    return m_bit_board.get(position);
  }

  inline void set(const Position& position, const bool value)
  {
    m_bit_board.set(position, value);
  }

  constexpr const BitBoard& bit_board() const
  {
    return m_bit_board;
  }

  inline std::vector<Position> positions() const
  {
    return m_bit_board.positions();
  }

private:
  const Piece* m_piece;

  BitBoard m_bit_board;
};

} // namespace olaf

#endif // PIECEBOARD_H

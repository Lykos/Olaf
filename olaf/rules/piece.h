#ifndef PIECETYPE_H
#define PIECETYPE_H

#include <vector>

#include "olaf/rules/position.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/color.h"

namespace olaf
{

class IncompleteMove;

class Move;

class ChessBoard;

class Piece;

bool operator==(const Piece& a, const Piece& b);

/**
 * @brief The Piece class is an abstract class which represents a particular piece type (e.g. Knight)
 */
class Piece
{
  friend bool operator==(const Piece& a, const Piece& b);

public:
  typedef int piece_index_t;

  /**
   * @brief Piece creates a new base piece.
   * @param piece_index the index of this piece in lists that contain somethin for all pieces.
   * @param symbol the char which is used to represent this piece.
   * @param initial_board the bitboard which will serve as the initial
   *        board for white.
   */
  Piece(piece_index_t piece_index,
        char symbol,
        const BitBoard& initial_board);

  piece_index_t piece_index() const;

  char symbol(Color color) const;

  BitBoard initial_board(Color color) const;

  static const piece_index_t c_no_piece = -1;

private:
  const piece_index_t m_piece_index;

  const char m_symbol;

  const BitBoard m_initial_board;
};

} // namespace olaf

#include "olaf/rules/move.h"

#endif // PIECETYPE_H

#ifndef PIECETYPE_H
#define PIECETYPE_H

#include "position.h"
#include "color.h"
#include "bitboard.h"
#include <vector>

class Move;

class ChessBoard;

/**
 * @brief The Piece class is an abstract class which represents a particular piece type (e.g. Knight)
 */
class Piece
{
public:
  typedef std::uint_fast8_t piece_index_t;

  Piece(piece_index_t, const BitBoard&);

  /**
   * @brief moves
   * @param source
   * @param color
   * @param opponents Biboard that marks squares occupied by an opposing piece.
   * @param occupied Bitboard that marks occupied squares.
   * @return
   */
  virtual std::vector<Move> moves(const Position &source,
                                  const ChessBoard &board,
                                  const BitBoard &opponents,
                                  const BitBoard &friends) const = 0;

  piece_index_t piece_index() const;

  const BitBoard& initial_board() const;

private:
  piece_index_t m_piece_index;

  BitBoard m_initial_board;

};

#include "chessboard.h"

#endif // PIECETYPE_H

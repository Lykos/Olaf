#ifndef PIECETYPE_H
#define PIECETYPE_H

#include "position.h"
#include "color.h"
#include "bitboard.h"
#include <vector>

class Move;

class ChessBoard;

class Piece;

bool operator==(const Piece &a, const Piece &b);

/**
 * @brief The Piece class is an abstract class which represents a particular piece type (e.g. Knight)
 */
class Piece
{
  friend bool operator==(const Piece &a, const Piece &b);

public:
  typedef std::uint_fast8_t piece_index_t;

  Piece(piece_index_t, const BitBoard&);

  virtual std::vector<Move> moves(const Position &source, const ChessBoard &board) const = 0;

  piece_index_t piece_index() const;

  const BitBoard& initial_board() const;

  virtual bool can_move(const Position &source, const Position &destination, const ChessBoard &board) const = 0;

  virtual Move move(const Position &source, const Position &destination, const ChessBoard &board) const = 0;

  virtual ~Piece() {}

private:
  piece_index_t m_piece_index;

  BitBoard m_initial_board;

};

#include "chessboard.h"

#endif // PIECETYPE_H

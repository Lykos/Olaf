#ifndef COLORBOARD_H
#define COLORBOARD_H

class PieceBoard;

#include "color.h"
#include "position.h"
#include <vector>
#include <cstdint>

/**
 * @brief The ColorBoard class represents all the board information about one color, i.e. castling rights and
 * piece positions.
 */
class ColorBoard
{
public:
  typedef std::uint_fast8_t piece_index_t;

  /**
   * @brief ColorBoard
   * @param color
   * @param piece_boards
   * @param can_castle_q True if queenside castling is possible.
   * @param can_castle_k True if queenside castling is possible.
   */
  ColorBoard(const std::vector<PieceBoard>& piece_boards = std::vector<PieceBoard>(), bool can_castle_q = true, bool can_castle_k = true);

  const std::vector<PieceBoard>& piece_boards() const;

  /**
   * @brief piece_board returns the bitboard that belongs to a given piece.
   * @param piece_index the index of the piece.
   * @return the PieceBoard of that piece.
   */
  PieceBoard& piece_board(piece_index_t piece_index);

  /**
   * @brief piece_board returns the bitboard that belongs to a given piece.
   * @param piece_index the index of the piece.
   * @return the PieceBoard of that piece.
   */
  const PieceBoard& piece_board(piece_index_t piece_index) const;

  piece_index_t piece_index(const Position&) const;

  const Piece& piece(const Position&) const;

  bool can_castle_q() const;

  bool can_castle_k() const;

  void can_castle_q(bool new_can_castle_q);

  void can_castle_k(bool new_can_castle_k);

  BitBoard occupied() const;

private:
  std::vector<PieceBoard> m_piece_boards;

  bool m_can_castle_q;

  bool m_can_castle_k;

};

ColorBoard create_initial_color_board(Color);

#include "pieceboard.h"

#endif // COLORBOARD_H

#ifndef COLORBOARD_H
#define COLORBOARD_H

#include <array>
#include <memory>

#include "color.h"
#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/bitboard.h"

namespace olaf
{

class ColorBoard;

bool operator ==(const ColorBoard& left, const ColorBoard& right);

/**
 * @brief The ColorBoard class represents all the board information about one color, i.e. castling rights and
 * piece positions.
 */
class ColorBoard
{
  friend bool operator ==(const ColorBoard& left, const ColorBoard& right);
public:
  static ColorBoard create_initial_color_board(Color);

  static ColorBoard create_empty_color_board();

  typedef std::array<BitBoard, PieceSet::c_no_pieces> PieceBoards;

  /**
   * @brief ColorBoard
   * @param color
   * @param piece_boards
   * @param can_castle_q True if queenside castling is possible.
   * @param can_castle_k True if queenside castling is possible.
   */
  explicit ColorBoard(const PieceBoards& piece_boards = PieceBoards(),
                      bool can_castle_q = true,
                      bool can_castle_k = true);

  const PieceBoards& piece_boards() const;

  /**
   * @brief piece_board returns the bitboard that belongs to a given piece.
   * @param piece_index the index of the piece.
   * @return the BitBoard of that piece.
   */
  BitBoard& piece_board(Piece::piece_index_t piece_index);

  /**
   * @brief piece_board returns the bitboard that belongs to a given piece.
   * @param piece_index the index of the piece.
   * @return the BitBoard of that piece.
   */
  const BitBoard& piece_board(Piece::piece_index_t piece_index) const;

  bool can_castle_q() const;

  bool can_castle_k() const;

  bool can_castle() const;

  void can_castle_q(bool new_can_castle_q);

  void can_castle_k(bool new_can_castle_k);

  BitBoard occupied() const;

  bool dead() const;

private:
  PieceBoards m_piece_boards;

  bool m_can_castle_q;

  bool m_can_castle_k;

};

} // namespace olaf

#endif // COLORBOARD_H

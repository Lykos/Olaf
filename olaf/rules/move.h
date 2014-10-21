#ifndef MOVE_H
#define MOVE_H

#include <cstdint>
#include <ostream>

#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/bitboard.h"

namespace olaf
{

class UndoInfo;
class Move;

/**
 * @brief IncompleteMove is used for a move for which the flags have not been set.
 */
typedef Move IncompleteMove;

constexpr bool operator ==(const Move a, const Move b);

class Move
{
  friend constexpr bool operator ==(const Move a, const Move b);
public:
  constexpr Move():
    m_state(0)
  {}

  constexpr Move(const Position& source,
                 const Position& destination,
                 const std::uint16_t flags):
    m_state(flags | BitBoard::index(source) << 6 | BitBoard::index(destination))
  {}

  /**
   * @brief complete creates a new move for which the flags are set correctly.
   */
  static Move complete(IncompleteMove incomplete_move,
                       const ChessBoard& board);
  inline static Move complete(const Position& source,
                              const Position& destination,
                              const ChessBoard& board)
  {
    return complete(incomplete(source, destination), board);
  }
  inline static Move complete_promotion(const Position& source,
                                        const Position& destination,
                                        const Piece::piece_index_t created_piece,
                                        const ChessBoard& board)
  {
    return complete(incomplete_promotion(source, destination, created_piece), board);
  }

  static constexpr IncompleteMove incomplete(
      const Position& source,
      const Position& destination)
  {
    return Move(source, destination, 0);
  }

  static constexpr IncompleteMove incomplete_promotion(
      const Position& source,
      const Position& destination,
      const Piece::piece_index_t created_piece)
  {
    return Move(source, destination, created_piece << 12 | c_promotion_flag);
  }

  bool is_pseudo_valid(const ChessBoard& board) const;

  /**
   * @brief execute executes the moves.
   */
  void execute(ChessBoard* board, UndoInfo* undo_info) const;

  /**
   * @brief undo takes back the move actions.
   */
  void undo(const UndoInfo& undo_info, ChessBoard* board) const;

  constexpr Position source() const
  {
    return BitBoard::reverse_index((m_state >> 6) & 0x3f);
  }

  constexpr Position destination() const
  {
    return BitBoard::reverse_index(m_state & 0x3f);
  }

  static const std::uint16_t c_special0_flag = 1 << 12;
  static const std::uint16_t c_special1_flag = 1 << 13;
  static const std::uint16_t c_capture_flag = 1 << 14;
  static const std::uint16_t c_promotion_flag = 1 << 15;
  static const std::uint16_t c_ep_mask = c_special0_flag | c_special1_flag | c_capture_flag | c_promotion_flag;
  static const std::uint16_t c_ep_flag = c_special1_flag | c_capture_flag;
  static const std::uint16_t c_castle_k_mask = c_capture_flag | c_promotion_flag | c_special1_flag | c_special0_flag;
  static const std::uint16_t c_castle_k_flag = c_special1_flag;
  static const std::uint16_t c_castle_q_mask = c_capture_flag | c_promotion_flag | c_special1_flag | c_special0_flag;
  static const std::uint16_t c_castle_q_flag = c_special1_flag | c_special0_flag;
  static const std::uint16_t c_castle_mask = c_capture_flag | c_promotion_flag | c_special1_flag;
  static const std::uint16_t c_castle_flag = c_special1_flag;
  static const std::uint16_t c_double_pawn_push_mask = c_capture_flag | c_promotion_flag | c_special1_flag | c_special0_flag;
  static const std::uint16_t c_double_pawn_push_flag = c_special1_flag | c_special0_flag;

  constexpr bool is_capture() const
  {
    return (m_state & c_capture_flag) != 0;
  }

  bool is_double_pawn_push() const
  {
    return (m_state & c_double_pawn_push_mask) == c_double_pawn_push_mask;
  }

  bool is_promotion() const
  {
    return (m_state & c_promotion_flag) != 0;
  }

  bool is_ep() const
  {
    return (m_state & c_ep_mask) == c_ep_mask;
  }

  bool is_king_castle() const
  {
    return (m_state & c_castle_k_flag) == c_castle_k_mask;
  }

  bool is_queen_castle() const
  {
    return (m_state & c_castle_q_flag) == c_castle_q_mask;
  }

  bool is_castle() const
  {
    return (m_state & c_castle_mask) == c_castle_flag;
  }

  Piece::piece_index_t created_piece() const
  {
    return (m_state >> 12) & 3;
  }

private:
  std::uint16_t m_state;
};

constexpr bool operator ==(const Move a, const Move b)
{
  return a.m_state == b.m_state;
}

std::ostream& operator <<(std::ostream& out, Move move);

} // namespace olaf

#endif // MOVE_H

#ifndef MOVE_H
#define MOVE_H

#include <cstdint>
#include <ostream>

#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/bitboard.h"

namespace olaf
{

class IncompleteMove;
class MoveChecker;

constexpr bool operator ==(const IncompleteMove a, const IncompleteMove b);

/**
 * @brief IncompleteMove is used for a move for which the flags have not been set.
 */
class IncompleteMove
{
  friend class MoveChecker;
  friend constexpr bool operator ==(const IncompleteMove a, const IncompleteMove b);
public:
  constexpr IncompleteMove():
    m_state(0)
  {}

  constexpr IncompleteMove(const Position source,
                           const Position destination):
    IncompleteMove(source, destination, 0)
  {}

  static constexpr IncompleteMove promotion(
      const Position source,
      const Position destination,
      const Piece::piece_index_t created_piece)
  {
    return IncompleteMove(source, destination, created_piece << 12 | c_promotion_flag);
  }

  bool is_pseudo_valid(const ChessBoard& board) const;

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
  static const std::uint16_t c_double_pawn_push_flag = c_special0_flag;

  constexpr bool is_capture() const
  {
    return (m_state & c_capture_flag) != 0;
  }

  bool is_double_pawn_push() const
  {
    return (m_state & c_double_pawn_push_mask) == c_double_pawn_push_flag;
  }

  bool is_promotion() const
  {
    return (m_state & c_promotion_flag) != 0;
  }

  bool is_ep() const
  {
    return (m_state & c_ep_mask) == c_ep_flag;
  }

  bool is_king_castle() const
  {
    return (m_state & c_castle_k_mask) == c_castle_k_flag;
  }

  bool is_queen_castle() const
  {
    return (m_state & c_castle_q_mask) == c_castle_q_flag;
  }

  bool is_castle() const
  {
    return (m_state & c_castle_mask) == c_castle_flag;
  }

  Piece::piece_index_t created_piece() const
  {
    return (m_state >> 12) & 3;
  }

protected:
  constexpr IncompleteMove(const Position source,
                           const Position destination,
                           const std::uint16_t flags):
    m_state(flags | source.index() << 6 | destination.index())
  {}

private:
  std::uint16_t m_state;
};

class UndoInfo;

class Move : public IncompleteMove {
  friend class MoveChecker;
public:
  constexpr Move()
  {}

  /**
   * @brief execute executes the moves.
   */
  void execute(ChessBoard* board, UndoInfo* undo_info, bool update_incremental_state = true) const;

  /**
   * @brief undo takes back the move actions.
   */
  void undo(const UndoInfo& undo_info, ChessBoard* board, bool update_incremental_state = true) const;
private:
  constexpr Move(const Position source,
                 const Position destination,
                 const std::uint16_t flags):
    IncompleteMove(source, destination, flags)
  {}
};

constexpr bool operator ==(const IncompleteMove a,
                           const IncompleteMove b)
{
  return a.m_state == b.m_state;
}

std::ostream& operator <<(std::ostream& out, IncompleteMove move);

std::ostream& operator <<(std::ostream& out, Move move);

} // namespace olaf

#endif // MOVE_H

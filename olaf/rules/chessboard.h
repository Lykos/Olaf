#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <cstdint>
#include <vector>
#include <array>
#include <ostream>

#include "olaf/rules/color.h"
#include "olaf/rules/colorboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/piece.h"
#include "olaf/transposition_table/zobristhash.h"
#include "olaf/evaluation/incrementalupdater.h"

namespace olaf
{

class ChessBoard;

std::ostream& operator <<(std::ostream& out, const ChessBoard& board);

bool operator ==(const ChessBoard& left, const ChessBoard& right);

// TODO 50 move rule
/**
 * @brief The ChessBoard class represents the whole chessboard including information about the positions
 * of all the pieces, the player whose turn it is, castling rights, e.p. rights etc.
 */
class ChessBoard
{
  friend std::ostream& operator <<(std::ostream& out, const ChessBoard& board);
  friend bool operator ==(const ChessBoard& left, const ChessBoard& right);
  friend class ZobristHash;
  friend class IncrementalUpdater;

public:
  ChessBoard(
      const std::array<ColorBoard, c_no_colors>& color_boards = {{ColorBoard(), ColorBoard()}},
      Color turn_color = Color::White,
      const BitBoard ep_captures = BitBoard());

  const ColorBoard& color_board(Color color) const;

  const ColorBoard& turn_board() const;

  const ColorBoard& noturn_board() const;

  inline bool ep_possible() const
  {
    return m_ep_captures;
  }

  /**
   * @brief ep_captures returns a bitboard indicating at which en passent capture is possible.
   */
  inline BitBoard ep_captures() const
  {
    return m_ep_captures;
  }

  inline void disable_ep()
  {
    ep_captures(BitBoard(0));
  }

  void ep_captures(const BitBoard new_ep_captures);

  Color noturn_color() const
  {
    return other_color(m_turn_color);
  }

  inline Color turn_color() const
  {
    return m_turn_color;
  }

  void turn_color(Color new_turn_color);

  inline int turn_number() const
  {
    return m_turn_number;
  }

  inline void turn_number(const int new_turn_number)
  {
    m_turn_number = new_turn_number;
  }

  /**
   * @brief next_turn advances to the next turn. In order to make all things this updates work
   *        properly, this should be the last thing that is done when a move is executed.
   */
  void next_turn();

  /**
   * @brief next_turn advances to the next turn. In order to make all things this updates work
   *        properly, this should be the first thing that is done when a move is undone.
   */
  void previous_turn();

  inline int reversible_plies() const
  {
    return m_reversible_plies;
  }

  inline void reversible_plies(int new_reversible_plies)
  {
    m_reversible_plies = new_reversible_plies;
  }

  inline void reset_reversible_plies()
  {
    m_reversible_plies = 0;
  }

  inline void increment_reversible_plies()
  {
    ++m_reversible_plies;
  }

  /**
   * @attention Result caching might be invalid if the user is not careful.
   * @brief opponents returns a bitboard indicating positions at which an opposing piece
   * is present and caches the result until the next turn flip.
   */
  BitBoard opponents() const;

  /**
   * @brief opponent is a shortcut for opponents().get(position)
   */
  bool opponent(Position position) const;

  /**
   * @attention Result caching might be invalid if the user is not careful.
   * @brief opponents returns a bitboard indicating positions at which a friendly piece
   * is present and caches the result until the next turn flip.
   */
  BitBoard friends() const;

  /**
   * @brief friendd is a shortcut for friends().get(position)
   * @return
   */
  bool friendd(Position position) const;

  /**
   * @attention Result caching might be invalid if the user is not careful.
   * @brief opponents returns a bitboard indicating positions at which any piece
   * is present and caches the result until the next turn flip.
   */
  BitBoard occupied() const;

  /**
   * @brief occupied is a shortcut for occupied().get(position)
   */
  bool occupied(Position position) const;

  /**
   * @brief won returns true if the given color has won, i.e.
   *        if black has no king. Note that this is not strictly
   *        according to the chess rules, but it fits the engine.
   */
  inline bool won(const Color color) const
  {
    return m_color_boards[1 - static_cast<int>(color)].dead();
  }

  /**
   * @brief draw returns true if the game is a draw.
   */
  inline bool draw() const
  {
    if (!m_draw_valid) {
      calculate_draw();
    }
    return m_draw;
  }

  /**
   * @brief finished returns true if the game is finished.
   */
  inline bool finished() const
  {
    return won(Color::White) || won(Color::Black) || draw();
  }

  /**
   * @brief add_piece adds a piece at the specific location.
   */
  void add_piece(Color color,
                 Piece::piece_index_t piece_index,
                 Position position);

  /**
   * @brief remove_piece removes a piece at the location in question.
   */
  void remove_piece(Color color,
                    Piece::piece_index_t piece_index,
                    Position position);

  /**
   * @brief can_castle_k sets the king castling right for the given color.
   */
  void can_castle_k(Color color, bool new_can_castle_k);

  /**
   * @brief can_castle_k sets the queen castling right for the given color.
   */
  void can_castle_q(Color color, bool new_can_castle_q);

  /**
   * @brief king_capture_positions returns the squares at which the king can be captured
   *        except for his own square. This is only non-empty after castling.
   */
  inline BitBoard king_captures() const
  {
    return m_king_captures;
  }

  inline void king_captures(const BitBoard new_king_captures)
  {
    m_king_captures = new_king_captures;
  }

  inline void disable_king_captures()
  {
    king_captures(BitBoard(0));
  }

  inline ZobristHash::hash_t zobrist_hash() const
  {
    return m_zobrist_hash;
  }

  /**
   * @brief incremental_score returns the score regarding all the things that are updated incrementally.
   *        It always returns the score for the side whose turn it is;
   */
  inline int incremental_score() const
  {
    return m_turn_color == Color::White ? m_incremental_score_white : -m_incremental_score_white;
  }

  inline Piece::piece_index_t piece_index(const Position pos) const
  {
    return m_pieces[pos.index()];
  }

  const Piece& piece(const Position pos) const;

private:
  void calculate_draw() const;

  std::array<ColorBoard, c_no_colors> m_color_boards;

  std::array<Piece::piece_index_t, Position::c_index_size> m_pieces;

  Color m_turn_color;

  int m_turn_number = 1;

  std::int_fast8_t m_reversible_plies = 0;

  BitBoard m_ep_captures;

  BitBoard m_king_captures;

  ZobristHash::hash_t m_zobrist_hash;

  int m_incremental_score_white;

  std::vector<ZobristHash::hash_t> m_hashes;

  mutable bool m_draw;

  mutable bool m_opponents_valid = false;

  mutable bool m_friends_valid = false;

  mutable bool m_occupied_valid = false;

  mutable bool m_draw_valid = false;

  mutable BitBoard m_opponents;

  mutable BitBoard m_friends;

  mutable BitBoard m_occupied;
};

ChessBoard create_initial_board();

ChessBoard create_empty_board();

} // namespace olaf

#endif // CHESSBOARD_H

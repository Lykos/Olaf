#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <ostream>

#include "olaf/rules/color.h"
#include "olaf/rules/colorboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/piece.h"
#include "olaf/transposition_table/zobristhash.h"

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

public:
  /**
   * @brief ChessBoard
   * @param color_boards
   * @param turn
   * @param ep_possible
   * @param ep_capture_position
   * @param ep_vicitim_position
   */
  ChessBoard(
      const std::array<ColorBoard, 2> &color_boards = {{ColorBoard(), ColorBoard()}},
      Color turn = Color::White,
      bool ep_possible = false,
      const Position &ep_capture_position = Position(),
      const Position &ep_victim_position = Position());

  const ColorBoard& color_board(Color color) const;

  const ColorBoard& turn_board() const;

  const ColorBoard& noturn_board() const;

  /**
   * @brief ep_possible returns true  if en passent is possible.
   */
  bool ep_possible() const;

  /**
   * @brief ep_position returns the position at which en passent capture is possible.
   */
  const Position& ep_capture_position() const;

  /**
   * @brief ep_position returns the position at which en passent will capture a pawn.
   */
  const Position& ep_victim_position() const;

  void disable_ep();

  /**
   * @brief enable_ep enables en passent at the position it was last enabled.
   */
  void enable_ep();

  void enable_ep(const Position& victim_position,
                 const Position& capture_position);

  Color noturn_color() const;

  Color turn_color() const;

  void turn_color(Color new_turn_color);

  int turn_number() const;

  void turn_number(int new_turn_number);

  void next_turn();

  void previous_turn();

  /**
   * @attention Result caching might be invalid if the user is not careful.
   * @brief opponents returns a bitboard indicating positions at which an opposing piece
   * is present and caches the result until the next turn flip.
   * @return
   */
  const BitBoard& opponents() const;

  /**
   * @brief opponent is a shortcut for opponents().get(position)
   * @return
   */
  bool opponent(const Position&) const;

  /**
   * @attention Result caching might be invalid if the user is not careful.
   * @brief opponents returns a bitboard indicating positions at which a friendly piece
   * is present and caches the result until the next turn flip.
   * @return
   */
  const BitBoard& friends() const;

  /**
   * @brief friendd is a shortcut for friends().get(position)
   * @return
   */
  bool friendd(const Position&) const;

  /**
   * @attention Result caching might be invalid if the user is not careful.
   * @brief opponents returns a bitboard indicating positions at which any piece
   * is present and caches the result until the next turn flip.
   * @return
   */
  const BitBoard& occupied() const;

  /**
   * @brief occupied is a shortcut for occupied().get(position)
   * @return
   */
  bool occupied(const Position& position) const;

  /**
   * @brief finished returns true if the game is finished
   * @return
   */
  bool finished() const;

  /**
   * @brief add_piece adds a piece at the specific location.
   */
  void add_piece(Color color,
                 Piece::piece_index_t piece_index,
                 const Position& position);

  /**
   * @brief remove_piece removes a piece at the location in question.
   */
  void remove_piece(Color color,
                    Piece::piece_index_t piece_index,
                    const Position& position);

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
  const std::vector<Position>& king_capture_positions() const;

  void king_capture_positions(
      const std::vector<Position>& new_king_capture_positions);

  /**
   * @brief king_victim_position returns the square of the killed king if he is captured
   *        via king_capture_positions.
   */
  const Position& king_victim_position() const;

  void king_victim_position(const Position& new_king_victim_position);

  ZobristHash::hash_t zobrist_hash() const;

  void zobrist_hash(ZobristHash::hash_t new_zobrist_hash);

  /**
   * @brief xor_zobrist_hash xors the parameter to the zobrist hash.
   */
  void xor_zobrist_hash(ZobristHash::hash_t zobrist_hash);

private:
  std::array<ColorBoard, 2> m_color_boards;

  Color m_turn_color;

  int m_turn_number = 1;

  bool m_ep_possible;

  Position m_ep_capture_position;

  Position m_ep_victim_position;

  std::vector<Position> m_king_capture_positions;

  Position m_king_victim_position;

  ZobristHash::hash_t m_zobrist_hash;

  mutable bool m_opponents_valid = false;

  mutable bool m_friends_valid = false;

  mutable bool m_occupied_valid = false;

  mutable BitBoard m_opponents;

  mutable BitBoard m_friends;

  mutable BitBoard m_occupied;

};

ChessBoard create_initial_board();

ChessBoard create_empty_board();

} // namespace olaf

#endif // CHESSBOARD_H

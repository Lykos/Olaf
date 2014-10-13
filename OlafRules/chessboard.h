#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <ostream>

#include "color.h"
#include "colorboard.h"
#include "position.h"

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

  ColorBoard& color_board(Color color);

  const ColorBoard& turn_board() const;

  ColorBoard& turn_board();

  const ColorBoard& noturn_board() const;

  ColorBoard& noturn_board();

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

  void ep_possible(bool new_ep_possible);

  void ep_capture_position(const Position& position);

  void ep_victim_position(const Position& position);

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
   * @brief add_piece is a shortcut for
   *        board.color_board(color).piece_board(piece_index).set(position, true)
   */
  void add_piece(Color color,
                 Piece::piece_index_t piece_index,
                 const Position& position);

  /**
   * @brief positions returns all valid positions on the board in the order
   *        a8, b8, ..., h8, a7, b7, ...
   */
  std::vector<Position> positions() const;

private:
  std::array<ColorBoard, 2> m_color_boards;

  Color m_turn_color;

  int m_turn_number = 1;

  bool m_ep_possible;

  Position m_ep_capture_position;

  Position m_ep_victim_position;

  mutable bool m_opponents_valid = false;

  mutable bool m_friends_valid = false;

  mutable bool m_occupied_valid = false;

  mutable BitBoard m_opponents;

  mutable BitBoard m_friends;

  mutable BitBoard m_occupied;

};

ChessBoard create_initial_board();

ChessBoard create_empty_board();

#endif // CHESSBOARD_H

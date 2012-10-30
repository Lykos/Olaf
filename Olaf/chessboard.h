#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "color.h"
#include "colorboard.h"
#include "position.h"
#include <array>

/**
 * @brief The ChessBoard class represents the whole chessboard including information about the positions
 * of all the pieces, the player whose turn it is, castling rights, e.p. rights etc.
 */
class ChessBoard
{
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
      const std::array<ColorBoard, 2> &color_boards = {ColorBoard(), ColorBoard()},
      Color turn = White,
      bool ep_possible = false,
      const Position &ep_capture_position = Position(),
      const Position &ep_victim_position = Position()
  );

  const ColorBoard& color_board(Color) const;

  ColorBoard& color_board(Color);

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

  void ep_possible(bool);

  void ep_capture_position(const Position&);

  void ep_victim_position(const Position&);

  Color turn() const;

  void flip_turn();

private:
  std::array<ColorBoard, 2> m_color_boards;

  Color m_turn;

  bool m_ep_possible;

  Position m_ep_capture_position;

  Position m_ep_victim_position;

};

ChessBoard create_initial_board();

#endif // CHESSBOARD_H

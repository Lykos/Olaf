#include "chessboard.h"

using namespace std;

ChessBoard::ChessBoard(Color turn, const array<ColorBoard, 2> &color_boards, bool ep_possible, const Position& ep_capture_position, const Position& ep_victim_position):
  m_turn (turn),
  m_color_boards (color_boards),
  m_ep_possible (ep_possible),
  m_ep_capture_position (ep_capture_position),
  m_ep_victim_position (ep_victim_position)
{}

const ColorBoard& ChessBoard::color_board(Color color) const
{
  return m_color_boards[static_cast<uint_fast8_t>(color)];
}

ColorBoard& ChessBoard::color_board(Color color)
{
  return m_color_boards[static_cast<uint_fast8_t>(color)];
}

const ColorBoard& ChessBoard::turn_board() const
{
  return m_color_boards[static_cast<uint_fast8_t>(m_turn)];
}

ColorBoard& ChessBoard::turn_board()
{
  return m_color_boards[static_cast<uint_fast8_t>(m_turn)];
}

const ColorBoard& ChessBoard::noturn_board() const
{
  return m_color_boards[1 - static_cast<uint_fast8_t>(m_turn)];
}

ColorBoard& ChessBoard::noturn_board()
{
  return m_color_boards[1 - static_cast<uint_fast8_t>(m_turn)];
}

bool ChessBoard::ep_possible() const
{
  return m_ep_possible;
}

const Position& ChessBoard::ep_capture_position()
{
  return m_ep_capture_position;
}

const Position& ChessBoard::ep_victim_position()
{
  return m_ep_victim_position;
}

void ChessBoard::ep_possible(bool possible)
{
  m_ep_possible = possible;
}

void ChessBoard::ep_capture_position(const Position &position)
{
  m_ep_capture_position = position;
}

void ChessBoard::ep_victim_position(const Position &position)
{
  m_ep_victim_position = position;
}

Color ChessBoard::turn() const
{
  return m_turn;
}

void ChessBoard::flip_turn()
{
  m_turn = next(m_turn);
}

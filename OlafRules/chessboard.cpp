#include "chessboard.h"

using namespace std;

std::ostream& operator <<(std::ostream& out, const ChessBoard& board)
{
  for (int i = 7; i >= 0; --i) {
    for (int j = 0; j < 8; ++j) {
      const Position pos(i, j);
      if (board.friendd(pos)) {
        out << board.turn_board().piece(pos).symbol(board.turn_color());
      } else if (board.opponent(pos)) {
        out << board.noturn_board().piece(pos).symbol(previous(board.turn_color()));
      } else {
        out << ".";
      }
    }
    out << endl;
  }
  return out;
}

ChessBoard::ChessBoard(const array<ColorBoard, 2>& color_boards, Color turn,
                       const bool ep_possible,
                       const Position& ep_capture_position,
                       const Position& ep_victim_position):
  m_color_boards (color_boards),
  m_turn_color (turn),
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
  return m_color_boards[static_cast<uint_fast8_t>(m_turn_color)];
}

ColorBoard& ChessBoard::turn_board()
{
  return m_color_boards[static_cast<uint_fast8_t>(m_turn_color)];
}

const ColorBoard& ChessBoard::noturn_board() const
{
  return m_color_boards[1 - static_cast<uint_fast8_t>(m_turn_color)];
}

ColorBoard& ChessBoard::noturn_board()
{
  return m_color_boards[1 - static_cast<uint_fast8_t>(m_turn_color)];
}

bool ChessBoard::ep_possible() const
{
  return m_ep_possible;
}

const Position& ChessBoard::ep_capture_position() const
{
  return m_ep_capture_position;
}

const Position& ChessBoard::ep_victim_position() const
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

Color ChessBoard::turn_color() const
{
  return m_turn_color;
}

int ChessBoard::turn_number() const
{
  return m_turn_number;
}

void ChessBoard::next_turn()
{
  m_opponents_valid = false;
  m_friends_valid = false;
  m_occupied_valid = false;
  m_turn_color = next(m_turn_color);
  if (m_turn_color == White) {
    ++m_turn_number;
  }
}

void ChessBoard::previous_turn()
{
  m_opponents_valid = false;
  m_friends_valid = false;
  m_occupied_valid = false;
  m_turn_color = previous(m_turn_color);
  if (m_turn_color == Black) {
    --m_turn_number;
  }
}

const BitBoard& ChessBoard::opponents() const
{
  if (!m_opponents_valid) {
    m_opponents = noturn_board().occupied();
    m_opponents_valid = true;
  }
  return m_opponents;
}

bool ChessBoard::opponent(const Position &position) const
{
  return opponents().get(position);
}

const BitBoard& ChessBoard::friends() const
{
  if (!m_friends_valid) {
    m_friends = turn_board().occupied();
    m_friends_valid = true;
  }
  return m_friends;
}

bool ChessBoard::friendd(const Position &position) const
{
  return friends().get(position);
}

const BitBoard& ChessBoard::occupied() const
{
  if (!m_occupied_valid) {
    m_occupied = opponents() | friends();
    m_occupied_valid = true;
  }
  return m_occupied;
}

bool ChessBoard::occupied(const Position &position) const
{
  return occupied().get(position);
}

bool ChessBoard::finished() const
{
  // TODO
  return false;
}

ChessBoard create_initial_board()
{
  static const array<ColorBoard, 2> colors{{
      ColorBoard::create_initial_color_board(White),
      ColorBoard::create_initial_color_board(Black)}};
  return ChessBoard(colors);
}

ChessBoard create_empty_board()
{
  static const array<ColorBoard, 2> colors{{
      ColorBoard::create_empty_color_board(),
      ColorBoard::create_empty_color_board()}};
  return ChessBoard(colors);
}

#include "chessboard.h"

using namespace std;

namespace olaf
{

std::ostream& operator <<(std::ostream& out, const ChessBoard& board)
{
  for (Position::row_t row = Position::c_row_size - 1; row >= 0; --row) {
    for (Position::column_t column = 0; column < Position::c_column_size; ++column) {
      const Position pos(row, column);
      if (board.friendd(pos)) {
        out << board.turn_board().piece(pos).symbol(board.turn_color());
      } else if (board.opponent(pos)) {
        out << board.noturn_board().piece(pos).symbol(board.noturn_color());
      } else {
        out << ".";
      }
    }
    out << endl;
  }
  return out;
}

bool operator ==(const ChessBoard& left, const ChessBoard& right)
{
  if (&left == &right) {
    return true;
  }
  if (left.m_ep_possible != right.m_ep_possible) {
    return false;
  }
  if (left.m_ep_possible) {
    const bool ep_equal =
        left.m_ep_capture_position == right.m_ep_capture_position
        && left.m_ep_victim_position == right.m_ep_victim_position;
    if (!ep_equal) {
      return false;
    }
  }
  if (left.m_king_capture_positions != right.m_king_capture_positions) {
    return false;
  }
  if (!left.m_king_capture_positions.empty()
      && !(left.m_king_victim_position == right.m_king_victim_position)) {
    return false;
  }
  return left.m_turn_color == right.m_turn_color
      && left.m_turn_number == right.m_turn_number
      && left.m_color_boards == right.m_color_boards;
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

void ChessBoard::ep_possible(const bool possible)
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

Color ChessBoard::noturn_color() const
{
  return next(m_turn_color);
}

void ChessBoard::turn_color(const Color new_color)
{
  m_turn_color = new_color;
}

int ChessBoard::turn_number() const
{
  return m_turn_number;
}

void ChessBoard::turn_number(const int new_turn_number)
{
  m_turn_number = new_turn_number;
}

void ChessBoard::next_turn()
{
  m_opponents_valid = false;
  m_friends_valid = false;
  m_occupied_valid = false;
  m_turn_color = next(m_turn_color);
  if (m_turn_color == Color::White) {
    ++m_turn_number;
  }
}

void ChessBoard::previous_turn()
{
  m_opponents_valid = false;
  m_friends_valid = false;
  m_occupied_valid = false;
  m_turn_color = previous(m_turn_color);
  if (m_turn_color == Color::Black) {
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
  // TODO 50 moves rule, repetition
  return m_color_boards[0].finished() || m_color_boards[1].finished();
}

void ChessBoard::add_piece(const Color color,
                           const Piece::piece_index_t piece_index,
                           const Position& position)
{
  color_board(color).piece_board(piece_index).set(position, true);
}

const vector<Position>& ChessBoard::king_capture_positions() const
{
  return m_king_capture_positions;
}

void ChessBoard::king_capture_positions(
    const std::vector<Position>& new_king_capture_positions)
{
  m_king_capture_positions = new_king_capture_positions;
}

const Position& ChessBoard::king_victim_position() const
{
  return m_king_victim_position;
}

void ChessBoard::king_victim_position(
    const Position& new_king_victim_position)
{
  m_king_victim_position = new_king_victim_position;
}

ChessBoard create_initial_board()
{
  static const array<ColorBoard, 2> colors{{
      ColorBoard::create_initial_color_board(Color::White),
      ColorBoard::create_initial_color_board(Color::Black)}};
  return ChessBoard(colors);
}

ChessBoard create_empty_board()
{
  static const array<ColorBoard, 2> colors{{
      ColorBoard::create_empty_color_board(),
      ColorBoard::create_empty_color_board()}};
  return ChessBoard(colors);

} // namespace olaf
}

#include "olaf/rules/chessboard.h"

#include <algorithm>
#include <cassert>

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
  return left.m_turn_color == right.m_turn_color
      && left.m_turn_number == right.m_turn_number
      && left.m_color_boards == right.m_color_boards
      && left.m_incremental_score_white == right.m_incremental_score_white
      && left.m_zobrist_hash == right.m_zobrist_hash
      && left.m_ep_captures == right.m_ep_captures
      && left.m_king_captures == right.m_king_captures;
}

ChessBoard::ChessBoard(const array<ColorBoard, c_no_colors>& color_boards,
                       const Color turn_color,
                       const BitBoard ep_captures):
  m_color_boards(color_boards),
  m_turn_color(turn_color),
  m_ep_captures(ep_captures)
{
  ZobristHash::calculate(this);
  IncrementalUpdater::calculate(this);
  m_hashes.push_back(m_zobrist_hash);
}

const ColorBoard& ChessBoard::color_board(Color color) const
{
  return m_color_boards[static_cast<uint_fast8_t>(color)];
}

const ColorBoard& ChessBoard::turn_board() const
{
  return m_color_boards[static_cast<uint_fast8_t>(m_turn_color)];
}

const ColorBoard& ChessBoard::noturn_board() const
{
  return m_color_boards[1 - static_cast<uint_fast8_t>(m_turn_color)];
}

void ChessBoard::ep_captures(const BitBoard new_ep_captures)
{
  if (m_ep_captures) {
    ZobristHash::update_ep(m_ep_captures.first_position(), this);
  }
  m_ep_captures = new_ep_captures;
  if (new_ep_captures) {
    ZobristHash::update_ep(new_ep_captures.first_position(), this);
  }
}

void ChessBoard::turn_color(const Color new_color)
{
  if (new_color != m_turn_color) {
    m_turn_color = new_color;
    ZobristHash::update_turn_color(this);
  }
}

void ChessBoard::next_turn()
{
  m_draw_valid = false;
  m_opponents_valid = false;
  m_friends_valid = false;
  m_occupied_valid = false;
  m_turn_color = other_color(m_turn_color);
  ZobristHash::update_turn_color(this);
  if (m_turn_color == Color::White) {
    ++m_turn_number;
  }
  m_hashes.push_back(m_zobrist_hash);
}

void ChessBoard::previous_turn()
{
  m_hashes.pop_back();
  if (m_turn_color == Color::White) {
    --m_turn_number;
  }
  ZobristHash::update_turn_color(this);
  m_turn_color = other_color(m_turn_color);
  m_occupied_valid = false;
  m_friends_valid = false;
  m_opponents_valid = false;
  m_draw_valid = false;
}

BitBoard ChessBoard::opponents() const
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

BitBoard ChessBoard::friends() const
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

BitBoard ChessBoard::occupied() const
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

void ChessBoard::calculate_draw() const
{
  static const int_fast8_t c_draw_reversible_plies = 50;
  static const int_fast8_t c_draw_repetitions = 3;
  m_draw_valid = true;
  m_draw = m_reversible_plies >= c_draw_reversible_plies
      || count(m_hashes.begin(), m_hashes.end(), m_zobrist_hash) >= c_draw_repetitions;
}

void ChessBoard::add_piece(const Color color,
                           const Piece::piece_index_t piece_index,
                           const Position& position)
{
  m_color_boards[static_cast<int>(color)].piece_board(piece_index).set(position, true);
  ZobristHash::update(color, piece_index, position, this);
  IncrementalUpdater::add_piece(color, piece_index, position, this);
}

void ChessBoard::remove_piece(const Color color,
                              const Piece::piece_index_t piece_index,
                              const Position& position)
{
  m_color_boards[static_cast<int>(color)].piece_board(piece_index).set(position, false);
  ZobristHash::update(color, piece_index, position, this);
  IncrementalUpdater::remove_piece(color, piece_index, position, this);
}

void ChessBoard::can_castle_k(const Color color, const bool new_can_castle_k)
{
  ColorBoard& color_board = m_color_boards[static_cast<int>(color)];
  if (color_board.can_castle_k() != new_can_castle_k) {
    color_board.can_castle_k(new_can_castle_k);
    ZobristHash::update_castle_k(color, this);
  }
}

void ChessBoard::can_castle_q(const Color color, const bool new_can_castle_q)
{
  ColorBoard& color_board = m_color_boards[static_cast<int>(color)];
  if (color_board.can_castle_q() != new_can_castle_q) {
    color_board.can_castle_q(new_can_castle_q);
    ZobristHash::update_castle_q(color, this);
  }
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
}

} // namespace olaf

#include "olaf/rules/chessboard.h"

#include <algorithm>
#include <cassert>

using namespace std;

namespace olaf
{

std::ostream& operator <<(std::ostream& out, const ChessBoard& board)
{
  for (Position::index_t row = Position::c_row_size - 1; row >= 0; --row) {
    for (Position::index_t column = 0; column < Position::c_column_size; ++column) {
      const Position pos(row, column);
      if (board.friendd(pos)) {
        out << board.piece(pos).symbol(board.turn_color());
      } else if (board.opponent(pos)) {
        out << board.piece(pos).symbol(board.noturn_color());
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
  m_ep_captures(ep_captures),
  m_zobrist_hash(0),
  m_incremental_score_white(0)
{
  for (Color color : c_colors) {
    const ColorBoard& board = color_board(color);
    for (Piece::piece_index_t piece_index = 0; piece_index < PieceSet::c_no_pieces; ++piece_index) {
      BitBoard piece_board = board.piece_board(piece_index);
      while (piece_board) {
        add_piece(color, piece_index, piece_board.next_position());
      }
    }
  }
  ZobristHash::calculate(this);
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
  m_draw_valid = false;
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
                           const Position position)
{
  const int color_index = static_cast<int>(color);
  m_color_boards[color_index].piece_board(piece_index).set(position, true);
  m_occupied[color_index].set(position, true);
  m_pieces[position.index()] = piece_index;
  ZobristHash::update(color, piece_index, position, this);
  IncrementalUpdater::add_piece(color, piece_index, position, this);
}

void ChessBoard::remove_piece(const Color color,
                              const Piece::piece_index_t piece_index,
                              const Position position)
{
  const int color_index = static_cast<int>(color);
  m_pieces[position.index()] = PieceSet::c_no_pieces;
  m_occupied[color_index].set(position, false);
  m_color_boards[color_index].piece_board(piece_index).set(position, false);
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

const Piece& ChessBoard::piece(const Position pos) const
{
  return PieceSet::instance().piece(piece_index(pos));
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

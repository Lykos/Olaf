#include "olaf/rules/chessboard.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "olaf/evaluation/incrementalupdater.h"
#include "olaf/transposition_table/zobristhash.h"

using namespace std;

namespace olaf
{

bool piece_invariant(const ChessBoard& board)
{
  BitBoard pieces(0);
  for (const Position position : Position::all_positions()) {
    if (board.piece_index(position) != Piece::c_no_piece) {
      pieces.set(position, true);
    }
  }
  return pieces == board.occupied() && !(board.opponents() & board.friends());
}

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
  out << "turn color: " << (board.m_turn_color == Color::White ? "White" : "Black") << endl;
  out << "turn number: " << board.m_turn_number << endl;
  out << "reversible plies: " << int(board.m_reversible_plies) << endl;
  if (board.m_ep_captures) {
    out << "ep: " << board.m_ep_captures.first_position() << endl;
  }
  out << board.m_hash_state;
  return out;
}

bool operator ==(const ChessBoard& left, const ChessBoard& right)
{
  if (&left == &right) {
    return true;
  }
  return left.m_turn_color == right.m_turn_color
      && left.m_turn_number == right.m_turn_number
      && left.m_reversible_plies == right.m_reversible_plies
      && left.m_color_boards == right.m_color_boards
      && left.m_incremental_state == right.m_incremental_state
      && left.m_hash_state == right.m_hash_state
      && left.m_ep_captures == right.m_ep_captures
      && left.m_king_captures == right.m_king_captures;
}

#define NO Piece::c_no_piece
static array<Piece::piece_index_t, Position::c_index_size> c_empty_piece_board = {
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO,
  NO, NO, NO, NO, NO, NO, NO, NO
};
#undef NO

ChessBoard::ChessBoard(const array<ColorBoard, c_no_colors>& color_boards,
                       const Color turn_color,
                       const BitBoard ep_captures):
  m_color_boards(color_boards),
  m_pieces(c_empty_piece_board),
  m_turn_color(turn_color),
  m_ep_captures(ep_captures),
  m_occupied({0, 0})
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
  IncrementalUpdater::calculate(*this, &m_incremental_state);
  ZobristHash::calculate(*this, &m_hash_state);
  m_hashes.push_back(m_hash_state.zobrist_hash);
  assert(piece_invariant(*this));
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
    ZobristHash::update_ep(m_ep_captures.first_position(), &m_hash_state);
  }
  m_ep_captures = new_ep_captures;
  if (new_ep_captures) {
    ZobristHash::update_ep(new_ep_captures.first_position(), &m_hash_state);
  }
}

void ChessBoard::turn_color(const Color new_color)
{
  if (new_color != m_turn_color) {
    m_turn_color = new_color;
    ZobristHash::update_turn_color(&m_hash_state);
  }
}

void ChessBoard::next_turn()
{
  m_draw_valid = false;
  m_turn_color = other_color(m_turn_color);
  ZobristHash::update_turn_color(&m_hash_state);
  if (m_turn_color == Color::White) {
    ++m_turn_number;
  }
  m_hashes.push_back(m_hash_state.zobrist_hash);
}

void ChessBoard::previous_turn()
{
  m_hashes.pop_back();
  if (m_turn_color == Color::White) {
    --m_turn_number;
  }
  ZobristHash::update_turn_color(&m_hash_state);
  m_turn_color = other_color(m_turn_color);
  m_draw_valid = false;
}

bool ChessBoard::draw_50_moves() const
{
  static const int_fast8_t c_draw_reversible_plies = 50;
  return m_reversible_plies >= c_draw_reversible_plies;
}

bool ChessBoard::draw_insufficient_material() const
{
  return false ||
      // two kings
      (friends() == king_board(m_turn_color)
          && opponents() == king_board(noturn_color()))
      // active player one minor piece and one king, other player one king
      || (friends() == (king_board(m_turn_color)
                        | bishop_board(m_turn_color)
                        | knight_board(m_turn_color))
          && friends().number() == 2
          && opponents() == king_board(noturn_color()))
      // active player one king, other player one minor piece and one king
      || (opponents() == (king_board(noturn_color())
                          | bishop_board(noturn_color())
                          | knight_board(noturn_color()))
          && opponents().number() == 2
          && friends() == king_board(m_turn_color))
      // active player two knights and one king, other player one king
      || (friends() == (king_board(m_turn_color)
                        | knight_board(m_turn_color))
          && friends().number() == 3
          && opponents() == king_board(noturn_color()))
      // active player one king, other player two knights and one king
      || (opponents() == (king_board(noturn_color())
                          | knight_board(noturn_color()))
          && opponents().number() == 3
          && friends() == king_board(m_turn_color))
      // only two kings and two same color bishops
      || (friends() == (king_board(m_turn_color)
                        | bishop_board(m_turn_color))
          && opponents() == (king_board(noturn_color())
                             | bishop_board(noturn_color()))
          && friends().number() == 2
          && opponents().number() == 2
          && (bishop_board(m_turn_color).first_position().index() % 2
              == bishop_board(noturn_color()).first_position().index() % 2));
}

bool ChessBoard::draw_repetitions() const
{
  static const int_fast8_t c_draw_repetitions = 3;
  return count(m_hashes.begin(), m_hashes.end(), m_hash_state.zobrist_hash) >= c_draw_repetitions;
}

void ChessBoard::calculate_draw() const
{
  m_draw_valid = true;
  m_draw = draw_50_moves() || draw_insufficient_material() || draw_repetitions();
}

string ChessBoard::draw_reason() const
{
  assert(draw());
  if (draw_repetitions()) {
    return "Repetition";
  } else if (draw_insufficient_material()) {
    return "Insufficient material";
  } else if (draw_50_moves()) {
    return "50 moves rule";
  } else {
    return "";
  }
}

void ChessBoard::add_piece(const Color color,
                           const Piece::piece_index_t piece_index,
                           const Position position)
{
  assert(0 <= piece_index && piece_index < PieceSet::c_no_pieces);
  const int color_index = static_cast<int>(color);
  m_color_boards[color_index].piece_board(piece_index).set(position, true);
  m_occupied[color_index].set(position, true);
  m_pieces[position.index()] = piece_index;
  ZobristHash::update(color, piece_index, position, &m_hash_state);
  IncrementalUpdater::add_piece(color, piece_index, position, &m_incremental_state);
}

void ChessBoard::remove_piece(const Color color,
                              const Piece::piece_index_t piece_index,
                              const Position position)
{
  assert(0 <= piece_index && piece_index < PieceSet::c_no_pieces);
  const int color_index = static_cast<int>(color);
  m_pieces[position.index()] = Piece::c_no_piece;
  m_occupied[color_index].set(position, false);
  m_color_boards[color_index].piece_board(piece_index).set(position, false);
  ZobristHash::update(color, piece_index, position, &m_hash_state);
  IncrementalUpdater::remove_piece(color, piece_index, position, &m_incremental_state);
}

void ChessBoard::can_castle_k(const Color color, const bool new_can_castle_k)
{
  ColorBoard& color_board = m_color_boards[static_cast<int>(color)];
  if (color_board.can_castle_k() != new_can_castle_k) {
    color_board.can_castle_k(new_can_castle_k);
    ZobristHash::update_castle_k(color, &m_hash_state);
  }
}

void ChessBoard::can_castle_q(const Color color, const bool new_can_castle_q)
{
  ColorBoard& color_board = m_color_boards[static_cast<int>(color)];
  if (color_board.can_castle_q() != new_can_castle_q) {
    color_board.can_castle_q(new_can_castle_q);
    ZobristHash::update_castle_q(color, &m_hash_state);
  }
}

const Piece& ChessBoard::piece(const Position pos) const
{
  const Piece::piece_index_t index = piece_index(pos);
  assert(0 <= index && index < PieceSet::c_no_pieces);
  return PieceSet::instance().piece(index);
}

ChessBoard create_initial_board()
{
  const array<ColorBoard, 2> colors{{
      ColorBoard::create_initial_color_board(Color::White),
      ColorBoard::create_initial_color_board(Color::Black)}};
  return ChessBoard(colors);
}

ChessBoard create_empty_board()
{
  const array<ColorBoard, 2> colors{{
      ColorBoard::create_empty_color_board(),
      ColorBoard::create_empty_color_board()}};
  return ChessBoard(colors);
}

} // namespace olaf

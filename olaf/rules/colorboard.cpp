#include "olaf/rules/colorboard.h"
#include "olaf/rules/pieceset.h"
#include <cstdint>
#include <memory>

using namespace std;

namespace olaf
{

bool operator ==(const ColorBoard& left, const ColorBoard& right)
{
  if (&left == &right) {
    return true;
  }
  return left.m_can_castle_k == right.m_can_castle_k
      && left.m_can_castle_q == right.m_can_castle_q
      && left.m_piece_boards == right.m_piece_boards;
}

ColorBoard::ColorBoard(const PieceBoards& piece_boards,
                       const bool can_castle_q,
                       const bool can_castle_k):
  m_piece_boards(piece_boards),
  m_can_castle_q(can_castle_q),
  m_can_castle_k(can_castle_k)
{}


const ColorBoard::PieceBoards& ColorBoard::piece_boards() const
{
  return m_piece_boards;
}

const BitBoard& ColorBoard::piece_board(const Piece::piece_index_t piece_index) const
{
  return m_piece_boards[piece_index];
}


BitBoard& ColorBoard::piece_board(const Piece::piece_index_t piece_index)
{
  return m_piece_boards[piece_index];
}

bool ColorBoard::can_castle_q() const
{
  return m_can_castle_q;
}

bool ColorBoard::can_castle_k() const
{
  return m_can_castle_k;
}

bool ColorBoard::can_castle() const
{
  return m_can_castle_q || m_can_castle_k;
}

void ColorBoard::can_castle_q(const bool new_can_castle_q)
{
  m_can_castle_q = new_can_castle_q;
}

void ColorBoard::can_castle_k(const bool new_can_castle_k)
{
  m_can_castle_k = new_can_castle_k;
}

BitBoard ColorBoard::occupied() const
{
  BitBoard bla(0);
  for (const BitBoard& piece_board : m_piece_boards) {
    bla = bla | piece_board;
  }
  return bla;
}

bool ColorBoard::dead() const
{
  static const Piece::piece_index_t king_index = PieceSet::c_king_index;
  return !m_piece_boards[king_index];
}

// static
ColorBoard ColorBoard::create_initial_color_board(Color color)
{
  ColorBoard::PieceBoards piece_boards;
  for (const Piece* const piece : PieceSet::instance().pieces()) {
    const BitBoard initial_board = piece->initial_board(color);
    piece_boards[piece->piece_index()] = initial_board;
  }
  return ColorBoard(piece_boards, true, true);
}

// static
ColorBoard ColorBoard::create_empty_color_board()
{
  ColorBoard::PieceBoards piece_boards;
  for (Piece::piece_index_t piece_index = 0; piece_index < PieceSet::c_no_pieces; ++piece_index) {
    piece_boards[piece_index] = BitBoard(0);
  }
  return ColorBoard(piece_boards, false, false);
}

} // namespace olaf

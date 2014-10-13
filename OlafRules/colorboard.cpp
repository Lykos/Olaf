#include "colorboard.h"
#include "pieceset.h"
#include <cstdint>
#include <memory>

using namespace std;

bool operator ==(const ColorBoard& left, const ColorBoard& right)
{
  if (&left == &right) {
    return true;
  }
  return left.m_can_castle_k == right.m_can_castle_k
      && left.m_can_castle_q == right.m_can_castle_q
      && left.m_piece_boards == right.m_piece_boards;
}

ColorBoard::ColorBoard(const std::vector<PieceBoard>& piece_boards,
                       const bool can_castle_q,
                       const bool can_castle_k):
  m_piece_boards(piece_boards),
  m_can_castle_q(can_castle_q),
  m_can_castle_k(can_castle_k)
{}


const std::vector<PieceBoard>& ColorBoard::piece_boards() const
{
  return m_piece_boards;
}

const PieceBoard& ColorBoard::piece_board(const piece_index_t piece_index) const
{
  return m_piece_boards[piece_index];
}


PieceBoard& ColorBoard::piece_board(const piece_index_t piece_index)
{
  return m_piece_boards[piece_index];
}

ColorBoard::piece_index_t ColorBoard::piece_index(const Position &position) const
{
  const piece_index_t size = m_piece_boards.size();
  for (piece_index_t index = 0; index < size; ++index) {
    if (m_piece_boards[index].get(position)) {
      return index;
    }
  }
  return Piece::c_no_piece;
}

const Piece& ColorBoard::piece(const Position &position) const
{
  return m_piece_boards[piece_index(position)].piece();
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
  BitBoard bla (0);
  for (const PieceBoard &piece_board : m_piece_boards) {
    bla = bla | piece_board;
  }
  return bla;
}

// static
ColorBoard ColorBoard::create_initial_color_board(Color color)
{
  vector<PieceBoard> piece_boards;
  for (const Piece* const piece : PieceSet::instance().pieces()) {
    BitBoard initial_board = piece->initial_board(color);
    const PieceBoard piece_board(piece, initial_board);
    piece_boards.push_back(piece_board);
  }
  return ColorBoard(piece_boards, true, true);
}

// static
ColorBoard ColorBoard::create_empty_color_board()
{
  vector<PieceBoard> piece_boards;
  for (const Piece* const piece : PieceSet::instance().pieces()) {
    const BitBoard empty_board(0);
    const PieceBoard piece_board(piece, empty_board);
    piece_boards.push_back(piece_board);
  }
  return ColorBoard(piece_boards, false, false);
}

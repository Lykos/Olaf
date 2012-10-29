#include "colorboard.h"
#include <cstdint>

ColorBoard::ColorBoard(Color color, const std::vector<PieceBoard>& piece_boards, bool can_castle_q, bool can_castle_k):
  m_color (color),
  m_piece_boards (piece_boards),
  m_can_castle_q (can_castle_q),
  m_can_castle_k (can_castle_k)
{}


const std::vector<PieceBoard>& ColorBoard::piece_boards() const
{
  return m_piece_boards;
}

const PieceBoard& ColorBoard::piece_board(piece_index_t piece_index) const
{
  return m_piece_boards[piece_index];
}


PieceBoard& ColorBoard::piece_board(piece_index_t piece_index)
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

void ColorBoard::can_castle_q(bool new_can_castle_q)
{
  m_can_castle_q = new_can_castle_q;
}

void ColorBoard::can_castle_k(bool new_can_castle_k)
{
  m_can_castle_k = new_can_castle_k;
}

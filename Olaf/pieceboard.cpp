#include "pieceboard.h"

PieceBoard::PieceBoard(const Piece *piece, const BitBoard &bit_board):
  m_piece (piece),
  m_bit_board (bit_board)
{}

PieceBoard::operator BitBoard() const
{
  return m_bit_board;
}

const Piece &PieceBoard::piece() const
{
  return *m_piece;
}

bool PieceBoard::get(const Position &position) const
{
  return m_bit_board.get(position);
}

void PieceBoard::set(const Position &position, bool value)
{
  m_bit_board.set(position, value);
}

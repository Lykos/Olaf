#include "pieceboard.h"

using namespace std;

bool operator ==(const PieceBoard& left, const PieceBoard& right)
{
  if (&left == &right) {
    return true;
  }
  return left.m_piece == right.m_piece
      && left.m_bit_board == right.m_bit_board;
}

PieceBoard::PieceBoard(const Piece* const piece, const BitBoard& bit_board):
  m_piece(piece),
  m_bit_board(bit_board)
{}

PieceBoard::operator BitBoard() const
{
  return m_bit_board;
}

const Piece& PieceBoard::piece() const
{
  return *m_piece;
}

bool PieceBoard::get(const Position& position) const
{
  return m_bit_board.get(position);
}

void PieceBoard::set(const Position& position, const bool value)
{
  m_bit_board.set(position, value);
}

const BitBoard& PieceBoard::bit_board() const
{
  return m_bit_board;
}

#include "piece.h"

Piece::Piece(piece_index_t piece_index, const BitBoard &initial_board):
  m_piece_index (piece_index),
  m_initial_board (initial_board)
{}

Piece::piece_index_t Piece::piece_index() const
{
  return m_piece_index;
}

const BitBoard& Piece::initial_board() const
{
  return m_initial_board;
}

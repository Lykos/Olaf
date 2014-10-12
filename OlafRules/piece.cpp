#include "piece.h"

#include <cassert>
#include <cctype>

#include "color.h"

using namespace std;

bool operator==(const Piece &a, const Piece &b)
{
  return a.m_piece_index == b.m_piece_index;
}

Piece::Piece(const piece_index_t piece_index,
             const char symbol,
             const BitBoard& initial_board):
  m_piece_index(piece_index),
  m_symbol(symbol),
  m_initial_board(initial_board)
{
  assert(piece_index != c_no_piece);
  assert(piece_index >= 0);
  assert(islower(symbol));
}

Piece::piece_index_t Piece::piece_index() const
{
  return m_piece_index;
}

char Piece::symbol(const Color color) const
{
  return color == Color::White ? m_symbol : toupper(m_symbol);
}

const BitBoard& Piece::initial_board() const
{
  return m_initial_board;
}

Piece::~Piece() {}

bool Piece::can_move(const Position& source,
                     const Position& destination,
                     const ChessBoard& board) const {
  return board.friendd(source)
      && !board.friendd(destination)
      && board.turn_board().piece_index(source) == m_piece_index;
}

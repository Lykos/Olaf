#include "colorboard.h"
#include "pieceset.h"
#include <cstdint>

using namespace std;

ColorBoard::ColorBoard(const std::vector<PieceBoard>& piece_boards, bool can_castle_q, bool can_castle_k):
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

ColorBoard::piece_index_t ColorBoard::piece_index(const Position &position) const
{
  for (piece_index_t index = 0; index < m_piece_boards.size(); ++index) {
    if (m_piece_boards[index].get(position)) {
      return index;
    }
  }
  return -1;
}

const Piece& ColorBoard::piece(const Position &position) const
{
  return m_piece_boards.at(piece_index(position)).piece();
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

BitBoard ColorBoard::occupied() const
{
  BitBoard bla (0);
  for (const PieceBoard &piece_board : m_piece_boards) {
    bla = bla | piece_board;
  }
  return bla;
}

ColorBoard create_initial_color_board(Color color)
{
  vector<PieceBoard> piece_boards;
  for (const Piece *piece : PieceSet::instance().pieces()) {
    BitBoard initial_board = piece->initial_board();
    if (color == Black) {
      initial_board = initial_board.mirror_rows();
    }
    PieceBoard piece_board (piece, initial_board);
    piece_boards.push_back(piece_board);
  }
  return ColorBoard(piece_boards);
}

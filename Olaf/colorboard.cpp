#include "colorboard.h"

ColorBoard::ColorBoard(const std::vector<PiecePositions>& piece_positions, const std::vector<PieceBoard>& piece_boards):
  m_piece_positions (piece_positions),
  m_piece_boards (piece_boards)
{}

const std::vector<PiecePositions>& ColorBoard::piece_positions() const
{
  return m_piece_positions;
}

const std::vector<PieceBoard>& ColorBoard::piece_boards() const
{
  return m_piece_boards;
}

#include "materialevaluator.h"
#include "pieceset.h"

MaterialEvaluator::MaterialEvaluator():
  m_piece_values (PieceSet::instance().pieces().size())
{
  const PieceSet &set;
  m_piece_values[set.rook()->piece_index()] = 500;
  m_piece_values[set.knight()->piece_index()] = 300;
  m_piece_values[set.bishop()->piece_index()] = 300;
  m_piece_values[set.queen()->piece_index()] = 900;
  m_piece_values[set.king()->piece_index()] = 1000000;
  m_piece_values[set.pawn()->piece_index()] = 100;
}

int MaterialEvaluator::evaluate(const ChessBoard &board)
{
  result = 0;
  for (const PieceBoard &piece_board : board.turn_board().piece_boards()) {
    result += piece_board.bit_board().number() * m_piece_values[piece_board.piece().piece_index()];
  }
  for (const PieceBoard &piece_board : board.noturn_board().piece_boards()) {
    result -= piece_board.bit_board().number() * m_piece_values[piece_board.piece().piece_index()];
  }
  return result;
}

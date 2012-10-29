#include "piecemoveaction.h"
#include <vector>

using namespace std;

PieceMoveAction::PieceMoveAction(ColorBoard::piece_index_t piece_index, const Position &source, const Position &destination):
  m_piece_index (piece_index),
  m_source (source),
  m_destination (destination)
{}

void PieceMoveAction::execute(ChessBoard& chess_board)
{
  chess_board.turn_board().piece_board(m_piece_index).set(m_source, false);
  chess_board.turn_board().piece_board(m_piece_index).set(m_destination, true);
}

void PieceMoveAction::undo(ChessBoard& chess_board)
{
  chess_board.turn_board().piece_board(m_piece_index).set(m_destination, false);
  chess_board.turn_board().piece_board(m_piece_index).set(m_source, true);
}

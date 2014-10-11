#include "captureaction.h"

CaptureAction::CaptureAction(const Position& victim_position,
                             const ColorBoard::piece_index_t victim_index):
  m_victim_position(victim_position),
  m_victim_index(victim_index)
{}

void CaptureAction::execute(ChessBoard* const chess_board)
{
  chess_board->noturn_board().piece_board(m_victim_index).set(m_victim_position, false);
}

void CaptureAction::undo(ChessBoard* const chess_board)
{
  chess_board->noturn_board().piece_board(m_victim_index).set(m_victim_position, true);
}

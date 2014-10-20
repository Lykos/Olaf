#include "olaf/rules/captureaction.h"

#include <cassert>
#include <memory>

using namespace std;

namespace olaf
{

CaptureAction::CaptureAction(const Position& victim_position,
                             const ColorBoard::piece_index_t victim_index):
  m_victim_position(victim_position),
  m_victim_index(victim_index)
{}

void CaptureAction::execute(ChessBoard* const board)
{
  assert(board->noturn_board().piece_board(m_victim_index).get(m_victim_position));
  const Color color = board->noturn_color();
  board->remove_piece(color, m_victim_index, m_victim_position);
}

void CaptureAction::undo(ChessBoard* const board)
{
  const Color color = board->noturn_color();
  board->add_piece(color, m_victim_index, m_victim_position);
}

unique_ptr<MoveAction> CaptureAction::copy() const
{
  return unique_ptr<MoveAction>(new CaptureAction(*this));
}

int CaptureAction::priority() const
{
  return MoveAction::CAPTURE_ACTION_PRIORITY;

} // namespace olaf
}

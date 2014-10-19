#include "olaf/rules/epdisableaction.h"

#include <memory>

#include "chessboard.h"

using namespace std;

namespace olaf
{

void EpDisableAction::execute(ChessBoard* const board)
{
  m_old_ep_possible = board->ep_possible();
  if (m_old_ep_possible) {
    m_old_ep_victim_position = board->ep_victim_position();
    m_old_ep_capture_position = board->ep_capture_position();
  }
  board->disable_ep();
}

void EpDisableAction::undo(ChessBoard* const board)
{
  if (m_old_ep_possible) {
    board->enable_ep(m_old_ep_victim_position,
                     m_old_ep_capture_position);
  }
}

unique_ptr<MoveAction> EpDisableAction::copy() const {
  return unique_ptr<MoveAction>(new EpDisableAction(*this));
}

int EpDisableAction::priority() const {
  return MoveAction::EP_DISABLE_PRIORITY;

} // namespace olaf
}

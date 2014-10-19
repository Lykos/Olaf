#include "olaf/rules/epenableaction.h"

#include <memory>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/position.h"

using namespace std;

namespace olaf
{

EpEnableAction::EpEnableAction(const Position& new_ep_capture_position,
                               const Position& new_ep_victim_position):
  m_new_ep_capture_position(new_ep_capture_position),
  m_new_ep_victim_position(new_ep_victim_position)
{}

void EpEnableAction::execute(ChessBoard* const board)
{
  m_old_ep_possible = board->ep_possible();
  if (m_old_ep_possible) {
    m_old_ep_capture_position = board->ep_capture_position();
    m_old_ep_victim_position = board->ep_victim_position();
  }
  board->enable_ep(m_new_ep_victim_position, m_new_ep_capture_position);
}

void EpEnableAction::undo(ChessBoard* const board)
{
  if (m_old_ep_possible) {
    board->enable_ep(m_old_ep_victim_position, m_old_ep_capture_position);
  } else {
    board->disable_ep();
  }
}

int EpEnableAction::priority() const {
  return MoveAction::EP_ENABLE_PRIORITY;
}

unique_ptr<MoveAction> EpEnableAction::copy() const {
  return unique_ptr<MoveAction>(new EpEnableAction(*this));

} // namespace olaf
}

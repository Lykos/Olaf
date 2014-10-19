#include "olaf/rules/epdisableaction.h"

#include <memory>

using namespace std;

namespace olaf
{

void EpDisableAction::execute(ChessBoard* const board)
{
  m_old_ep_possible = board->ep_possible();
  board->disable_ep();
}

void EpDisableAction::undo(ChessBoard* const board)
{
  board->enable_ep();
}

unique_ptr<MoveAction> EpDisableAction::copy() const {
  return unique_ptr<MoveAction>(new EpDisableAction(*this));
}

int EpDisableAction::priority() const {
  return MoveAction::EP_DISABLE_PRIORITY;

} // namespace olaf
}

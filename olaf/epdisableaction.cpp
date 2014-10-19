#include "epdisableaction.h"

#include <memory>

using namespace std;

namespace olaf
{

void EpDisableAction::execute(ChessBoard* const chess_board)
{
  m_old_ep_possible = chess_board->ep_possible();
  chess_board->ep_possible(false);
}

void EpDisableAction::undo(ChessBoard* const chess_board)
{
  chess_board->ep_possible(m_old_ep_possible);
}

unique_ptr<MoveAction> EpDisableAction::copy() const {
  return unique_ptr<MoveAction>(new EpDisableAction(*this));
}

int EpDisableAction::priority() const {
  return MoveAction::EP_DISABLE_PRIORITY;

} // namespace olaf
}

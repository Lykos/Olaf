#include "epenableaction.h"

#include <memory>

#include "chessboard.h"
#include "position.h"

using namespace std;

namespace olaf
{

EpEnableAction::EpEnableAction(const Position& new_ep_capture_position,
                               const Position& new_ep_victim_position):
  m_new_ep_capture_position(new_ep_capture_position),
  m_new_ep_victim_position(new_ep_victim_position)
{}

void EpEnableAction::execute(ChessBoard* const chess_board)
{
  m_old_ep_possible = chess_board->ep_possible();
  m_old_ep_capture_position = chess_board->ep_capture_position();
  m_old_ep_victim_position = chess_board->ep_victim_position();
  chess_board->ep_possible(true);
  chess_board->ep_capture_position(m_new_ep_capture_position);
  chess_board->ep_victim_position(m_new_ep_victim_position);
}

void EpEnableAction::undo(ChessBoard* const chess_board)
{
  chess_board->ep_capture_position(m_old_ep_capture_position);
  chess_board->ep_victim_position(m_old_ep_victim_position);
  chess_board->ep_possible(m_old_ep_possible);
}

int EpEnableAction::priority() const {
  return MoveAction::EP_ENABLE_PRIORITY;
}

unique_ptr<MoveAction> EpEnableAction::copy() const {
  return unique_ptr<MoveAction>(new EpEnableAction(*this));

} // namespace olaf
}

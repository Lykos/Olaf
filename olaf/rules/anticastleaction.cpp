#include "olaf/rules/anticastleaction.h"

#include <memory>

#include "olaf/rules/chessboard.h"
#include "olaf/rules/colorboard.h"

using namespace std;

namespace olaf
{

AntiCastleAction::AntiCastleAction(const bool forbid_castle_q, const bool forbid_castle_k):
  m_forbid_castle_q(forbid_castle_q),
  m_forbid_castle_k(forbid_castle_k)
{}

void AntiCastleAction::execute(ChessBoard* const board)
{
  const Color color = board->turn_color();
  const ColorBoard& color_board = board->turn_board();
  if (m_forbid_castle_k) {
    m_old_can_castle_k = color_board.can_castle_k();
    board->can_castle_k(color, false);
  }
  if (m_forbid_castle_q) {
    m_old_can_castle_q = color_board.can_castle_q();
    board->can_castle_q(color, false);
  }
}

void AntiCastleAction::undo(ChessBoard* const board)
{
  const Color color = board->turn_color();
  if (m_forbid_castle_k) {
    board->can_castle_k(color, m_old_can_castle_k);
  }
  if (m_forbid_castle_q) {
    board->can_castle_q(color, m_old_can_castle_q);
  }
}

unique_ptr<MoveAction> AntiCastleAction::copy() const
{
  return unique_ptr<MoveAction>(new AntiCastleAction(*this));
}

int AntiCastleAction::priority() const
{
  return MoveAction::ANTI_CASTLE_ACTION_PRIORITY;

} // namespace olaf
}

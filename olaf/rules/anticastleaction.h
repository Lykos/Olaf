#ifndef ANTICASTLEMOVE_H
#define ANTICASTLEMOVE_H

#include <memory>

#include "olaf/rules/moveaction.h"

namespace olaf
{

class ChessBoard;

/**
 * @brief The AntiCastleMove class represents a move action that changes the castling rights
 */
class AntiCastleAction : public MoveAction
{
public:
  /**
   * @brief AntiCastleMove
   * @param forbid_castle_q If this is true, queenside castling will be forbidden. If this is false, queenside castling
   * rights stay the same.
   * @param forbid_castle_k If this is true, kingside castling will be forbidden. If this is false, kingside castling
   * rights stay the same.
   */
  AntiCastleAction(bool forbid_castle_q, bool forbid_castle_k);

  void execute(ChessBoard* board) override;

  void undo(ChessBoard* board) override;

  std::unique_ptr<MoveAction> copy() const override;

  int priority() const override;

private:
  bool m_old_can_castle_q;

  bool m_old_can_castle_k;

  const bool m_forbid_castle_q;

  const bool m_forbid_castle_k;
};

} // namespace olaf

#endif // ANTICASTLEMOVE_H

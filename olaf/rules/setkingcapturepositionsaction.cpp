#include "olaf/rules/setkingcapturepositionsaction.h"

#include <memory>
#include <vector>

#include "olaf/rules/position.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/moveaction.h"

using namespace std;

namespace olaf
{

SetKingCapturePositionsAction::SetKingCapturePositionsAction(
    const std::vector<Position>& king_capture_positions,
    const Position& king_victim_position):
  m_new_king_capture_positions(king_capture_positions),
  m_new_king_victim_position(king_victim_position)
{}

void SetKingCapturePositionsAction::execute(ChessBoard* const chess_board)
{
  m_old_king_capture_positions = chess_board->king_capture_positions();
  m_old_king_victim_position = chess_board->king_victim_position();
  chess_board->king_capture_positions(m_new_king_capture_positions);
  chess_board->king_victim_position(m_new_king_victim_position);
}

void SetKingCapturePositionsAction::undo(ChessBoard* const chess_board)
{
  chess_board->king_capture_positions(m_old_king_capture_positions);
  chess_board->king_victim_position(m_old_king_victim_position);
}

int SetKingCapturePositionsAction::priority() const {
  return MoveAction::SET_KING_CAPTURE_POSITIONS_PRIORITY;
}

unique_ptr<MoveAction> SetKingCapturePositionsAction::copy() const {
  return unique_ptr<MoveAction>(new SetKingCapturePositionsAction(*this));

} // namespace olaf
}

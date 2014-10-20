#include "olaf/rules/conversionaction.h"

#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"

namespace olaf
{

ConversionAction::ConversionAction(const Position &position,
                                   const PieceSet::piece_index_t removed_piece,
                                   const PieceSet::piece_index_t created_piece):
  m_position(position),
  m_removed_piece(removed_piece),
  m_created_piece(created_piece)
{}

void ConversionAction::execute(ChessBoard* const board)
{
  const Color color = board->turn_color();
  board->remove_piece(color, m_removed_piece, m_position);
  board->add_piece(color, m_created_piece, m_position);
}

void ConversionAction::undo(ChessBoard* const board)
{
  const Color color = board->turn_color();
  board->remove_piece(color, m_created_piece, m_position);
  board->add_piece(color, m_removed_piece, m_position);
}

std::unique_ptr<MoveAction> ConversionAction::copy() const
{
  return std::unique_ptr<MoveAction>(new ConversionAction(*this));
}

int ConversionAction::priority() const
{
  return MoveAction::CONVERSION_ACTION_PRIORITY;

} // namespace olaf
}

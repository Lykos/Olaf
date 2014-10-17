#include "conversionaction.h"
#include "pieceset.h"

ConversionAction::ConversionAction(const Position &position,
                                   const PieceSet::piece_index_t removed_piece,
                                   const PieceSet::piece_index_t created_piece):
  m_position(position),
  m_removed_piece(removed_piece),
  m_created_piece(created_piece)
{}

void ConversionAction::execute(ChessBoard* const chess_board)
{
  chess_board->turn_board().piece_board(m_removed_piece).set(m_position, false);
  chess_board->turn_board().piece_board(m_created_piece).set(m_position, true);
}

void ConversionAction::undo(ChessBoard* const chess_board)
{
  chess_board->turn_board().piece_board(m_created_piece).set(m_position, false);
  chess_board->turn_board().piece_board(m_removed_piece).set(m_position, true);
}

std::unique_ptr<MoveAction> ConversionAction::copy() const
{
  return std::unique_ptr<MoveAction>(new ConversionAction(*this));
}

int ConversionAction::priority() const
{
  return MoveAction::CONVERSION_ACTION_PRIORITY;
}

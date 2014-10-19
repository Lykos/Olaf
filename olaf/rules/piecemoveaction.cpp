#include "olaf/rules/piecemoveaction.h"

#include <cassert>
#include <vector>

#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"
#include "olaf/rules/chessboard.h"

using namespace std;

namespace olaf
{

PieceMoveAction::PieceMoveAction(const Piece::piece_index_t piece_index,
                                 const Position& source,
                                 const Position& destination):
  m_piece_index(piece_index),
  m_source(source),
  m_destination(destination)
{}

void PieceMoveAction::execute(ChessBoard* const board)
{
  assert(board->turn_board().piece_index(m_source) == m_piece_index);
  const Color color = board->turn_color();
  board->remove_piece(color, m_piece_index, m_source);
  board->add_piece(color, m_piece_index, m_destination);
}

void PieceMoveAction::undo(ChessBoard* const board)
{
  const Color color = board->turn_color();
  board->remove_piece(color, m_piece_index, m_destination);
  board->add_piece(color, m_piece_index, m_source);
}

std::unique_ptr<MoveAction> PieceMoveAction::copy() const
{
  return std::unique_ptr<MoveAction>(new PieceMoveAction(*this));
}

int PieceMoveAction::priority() const
{
  return MoveAction::PIECE_MOVE_ACTION_PRIORITY;

} // namespace olaf
}

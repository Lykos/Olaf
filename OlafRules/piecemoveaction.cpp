#include "piecemoveaction.h"

#include <cassert>
#include <vector>

using namespace std;

PieceMoveAction::PieceMoveAction(const Piece::piece_index_t piece_index,
                                 const Position& source,
                                 const Position& destination):
  m_piece_index(piece_index),
  m_source(source),
  m_destination(destination)
{}

void PieceMoveAction::execute(ChessBoard* const chess_board)
{
  assert(chess_board->turn_board().piece_index(m_source) == m_piece_index);
  chess_board->turn_board().piece_board(m_piece_index).set(m_source, false);
  chess_board->turn_board().piece_board(m_piece_index).set(m_destination, true);
}

void PieceMoveAction::undo(ChessBoard* const chess_board)
{
  chess_board->turn_board().piece_board(m_piece_index).set(m_destination, false);
  chess_board->turn_board().piece_board(m_piece_index).set(m_source, true);
}

std::unique_ptr<MoveAction> PieceMoveAction::copy() const
{
  return std::unique_ptr<MoveAction>(new PieceMoveAction(*this));
}

int PieceMoveAction::priority() const
{
  return MoveAction::PIECE_MOVE_ACTION_PRIORITY;
}

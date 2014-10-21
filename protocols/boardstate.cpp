#include "boardstate.h"

#include "olaf/search/searcherfactory.h"
#include <utility>
#include "olaf/rules/undoinfo.h"

using namespace std;

namespace olaf
{

ChessBoard BoardState::copy_board() const
{
  unique_lock<mutex> lock(m_mutex);
  ChessBoard board(m_board);
  return board;
}

void BoardState::set_board(const ChessBoard& board)
{
  unique_lock<mutex> lock(m_mutex);
  m_board = board;
}

void BoardState::reset()
{
  set_board(create_initial_board());
}

void BoardState::undo()
{
  unique_lock<mutex> lock(m_mutex);
  if (!m_undoable_moves.empty()) {
    auto& undoable_move = m_undoable_moves.top();
    undoable_move.first.undo(undoable_move.second, &m_board);
    m_undoable_moves.pop();
  }
}

void BoardState::move(const Move& move)
{
  unique_lock<mutex> lock(m_mutex);
  m_undoable_moves.push(make_pair(move, UndoInfo()));
  auto& undoable_move = m_undoable_moves.top();
  undoable_move.first.execute(&m_board, &(undoable_move.second));
}

bool BoardState::valid_move(const IncompleteMove incomplete_move) const
{
  unique_lock<mutex> lock(m_mutex);
  return MoveChecker::valid_move(m_board, incomplete_move);
}

Move BoardState::create_move(const IncompleteMove incomplete_move) const
{
  unique_lock<mutex> lock(m_mutex);
  return Move::complete(incomplete_move, m_board);
}

} // namespace olaf

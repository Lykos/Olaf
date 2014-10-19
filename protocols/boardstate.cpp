#include "boardstate.h"

#include "olaf/search/searcherfactory.h"

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
  if (!m_moves.empty()) {
    m_moves.top().undo(&m_board);
    m_moves.pop();
  }
}

void BoardState::move(const Move& move)
{
  unique_lock<mutex> lock(m_mutex);
  m_moves.push(move);
  m_moves.top().execute(&m_board);
}

bool BoardState::valid_move(const Position& source,
                            const Position& destination)
{
  unique_lock<mutex> lock(m_mutex);
  return MoveCreator::valid_move(m_board, source, destination);
}

bool BoardState::valid_move(const Position& source,
                            const Position& destination,
                            const Piece::piece_index_t conversion)
{
  unique_lock<mutex> lock(m_mutex);
  return MoveCreator::valid_move(m_board, source, destination, conversion);
}

Move BoardState::create_move(const Position& source,
                             const Position& destination)
{
  unique_lock<mutex> lock(m_mutex);
  return MoveCreator::create_move(m_board, source, destination);
}

Move BoardState::create_move(const Position& source,
                             const Position& destination,
                             const Piece::piece_index_t conversion)
{
  unique_lock<mutex> lock(m_mutex);
  return MoveCreator::create_move(m_board, source, destination, conversion);

} // namespace olaf
}

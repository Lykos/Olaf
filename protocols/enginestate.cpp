#include "enginestate.h"

#include <cassert>

#include "boardstate.h"

using namespace std;
using namespace chrono;

namespace olaf
{

EngineState::EngineState(unique_ptr<TranspositionTable> transposition_table,
                         BoardState* const board_state):
  m_transposition_table(move(transposition_table)),
  m_board_state(board_state)
{
  assert(board_state);
}

SearchContext EngineState::create_search_context(const Stopper* const forced_stopper,
                                                 const Stopper* const weak_stopper) const
{
  SearchContext context;
  context.board = m_board_state->copy_board();
  context.forced_stopper = forced_stopper;
  context.weak_stopper = weak_stopper;
  if (m_my_turn && !m_force) {
    context.time_mode = SearchContext::TimeMode::BOUNDED;
  } else {
    context.time_mode = SearchContext::TimeMode::INFINITE;
  }
  context.transposition_table = m_transposition_table.get();
  return context;

} // namespace olaf
}

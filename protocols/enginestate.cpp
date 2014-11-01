#include "enginestate.h"

#include <cassert>

#include "boardstate.h"
#include "olaf/search/forcedstopper.h"

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

SearchContext EngineState::create_search_context()
{
  m_weak_stopper.reset(new ForcedStopper);
  m_forced_stopper.reset(new ForcedStopper);
  SearchContext context;
  context.board = m_board_state->copy_board();
  context.forced_stopper = m_forced_stopper.get();
  context.weak_stopper = m_weak_stopper.get();
  if (m_my_turn && !m_force) {
    context.time_mode = SearchContext::TimeMode::ADAPTED;
    context.total_time = m_my_time;
    context.increment = m_increment;
    if (m_moves == 0) {
      context.sudden_death = true;
    } else {
      context.sudden_death = false;
      context.moves_to_play = m_moves--;
    }
  } else {
    context.time_mode = SearchContext::TimeMode::INFINITE;
  }
  if (m_use_depth) {
    context.depth_mode = SearchContext::DepthMode::MAX_DEPTH;
    context.max_depth = m_depth;
  } else {
    context.depth_mode = SearchContext::DepthMode::ITERATIVE;
  }
  context.transposition_table = m_transposition_table.get();
  return context;

} // namespace olaf
}

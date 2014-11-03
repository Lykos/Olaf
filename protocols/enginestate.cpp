#include "enginestate.h"

#include <cassert>

#include "boardstate.h"
#include "olaf/search/forcedstopper.h"

using namespace std;
using namespace chrono;

namespace olaf
{

EngineState::EngineState(unique_ptr<TranspositionTable> transposition_table,
                         unique_ptr<EgbbProber> eggb_prober,
                         BoardState* const board_state):
  m_transposition_table(move(transposition_table)),
  m_egbb_prober(move(eggb_prober)),
  m_board_state(board_state),
  m_my_time(minutes(5)),
  m_opponent_time(minutes(5)),
  m_increment(0)
{
  assert(board_state);
}

void EngineState::reset_stoppers()
{
  m_weak_stopper.reset();
  m_forced_stopper.reset();
}

SearchContext EngineState::create_search_context()
{
  SearchContext context;
  context.board = m_board_state->copy_board();
  context.forced_stopper = &m_forced_stopper;
  context.weak_stopper = &m_weak_stopper;
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
  if (m_egbb_prober->is_initialized()) {
    context.prober = m_egbb_prober.get();
  }
  return context;
}

void EngineState::set_egt_path(const string& path)
{
  m_egbb_prober->load(path);
}

} // namespace olaf

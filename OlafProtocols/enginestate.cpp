#include "enginestate.h"

#include <cassert>

#include "boardstate.h"

using namespace std;
using namespace chrono;

EngineState::EngineState(BoardState* const board_state):
  m_board_state(board_state)
{
  assert(board_state);
}

bool EngineState::pondering() const
{
  return m_pondering && !m_deferred_pondering;
}

void EngineState::pondering(const bool value)
{
  m_pondering = value;
}

bool EngineState::my_turn() const
{
  return m_my_turn;
}

void EngineState::my_turn(const bool value)
{
  m_my_turn = value;
}

void EngineState::flip_turn()
{
  m_deferred_pondering = false;
  m_my_turn = !m_my_turn;
}

bool EngineState::force() const
{
  return m_force;
}

void EngineState::force(bool value)
{
  m_force = value;
}

void EngineState::deferred_pondering()
{
  m_deferred_pondering = true;
  m_pondering = true;
}

milliseconds EngineState::time() const
{
  return m_time;
}

void EngineState::time(const milliseconds &time)
{
  m_time = time;
}

const BoardState& EngineState::board_state() const
{
  return *m_board_state;
}

BoardState& EngineState::board_state()
{
  return *m_board_state;
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
  return context;
}

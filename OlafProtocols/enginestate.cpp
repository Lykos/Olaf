#include "enginestate.h"

bool EngineState::pondering() const
{
  return m_pondering && !m_deferred_pondering;
}

void EngineState::pondering(bool value)
{
  m_pondering = value;
}

bool EngineState::my_turn() const
{
  return m_my_turn;
}

void EngineState::my_turn(bool value)
{
  m_my_turn = value;
}

void EngineState::flip_turn()
{
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
}

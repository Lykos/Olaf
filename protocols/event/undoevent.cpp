#include "protocols/event/undoevent.h"

#include "protocols/boardstate.h"

namespace olaf
{

UndoEvent::UndoEvent(const int moves):
  m_moves(moves)
{}

void UndoEvent::execute(EngineState* const engine_state)
{
  for (int i = 0; i < m_moves; ++i) {
    engine_state->board_state().undo();
  }
}

} // namespace olaf

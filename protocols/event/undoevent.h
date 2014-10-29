#ifndef UNDOEVENT_H
#define UNDOEVENT_H

#include "protocols/event/engineevent.h"

namespace olaf
{

/**
 * @brief The UndoEvent class is an event that undoes a given number of moves.
 */
class UndoEvent : public EngineEvent
{
public:
  UndoEvent(int moves);

  void execute(EngineState* engine_state) override;

private:
  const bool m_moves;
};

} // namespace olaf

#endif // UNDOEVENT_H

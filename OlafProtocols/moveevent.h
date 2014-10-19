#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "engineevent.h"
#include "OlafSearching/move.h"

namespace olaf
{

/**
 * @brief The MoveEvent class is an event representing a move received
 *        from the chess interface program.
 */
class MoveEvent : public EngineEvent
{
public:
  MoveEvent(const Move& move);

  void execute(EngineState* engine_state) override;

private:
  const Move m_move;
};

} // namespace olaf

#endif // MOVEEVENT_H

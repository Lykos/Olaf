#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "protocols/event/engineevent.h"
#include "olaf/rules/move.h"

namespace olaf
{

/**
 * @brief The MoveEvent class is an event representing a move received
 *        from the chess interface program.
 */
class MoveEvent : public EngineEvent
{
public:
  MoveEvent(Move move);

  void execute(EngineState* engine_state) override;

private:
  const Move m_move;
};

} // namespace olaf

#endif // MOVEEVENT_H

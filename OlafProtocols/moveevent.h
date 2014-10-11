#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "engineevent.h"
#include "OlafRules/move.h"

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

#endif // MOVEEVENT_H

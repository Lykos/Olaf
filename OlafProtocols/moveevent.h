#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "engineevent.h"
#include "OlafRules/move.h"

class MoveEvent : public EngineEvent
{
public:
  MoveEvent(const Move& move);

  void execute(EngineState &engine_state);

private:
  Move m_move;

};

#endif // MOVEEVENT_H

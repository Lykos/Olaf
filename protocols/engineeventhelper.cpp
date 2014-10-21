#include "engineeventhelper.h"
#include "engineevent.h"
#include "moveevent.h"
#include "ponderingflipevent.h"
#include "forceflipevent.h"
#include "deferredponderingevent.h"
#include "myturnflipevent.h"
#include "pingevent.h"
#include "settimeevent.h"
#include "olaf/rules/move.h"
#include "olaf/parse/fenparser.h"
#include "setboardevent.h"

using namespace std;

namespace olaf
{

EngineEventHelper::EngineEventHelper(ProtocolWriter* const writer,
                                     BoardState* const board_state,
                                     Engine* const engine,
                                     ThinkingWriter* const thinking_writer):
  m_writer(writer),
  m_board_state(board_state),
  m_engine(engine),
  m_thinking_writer(thinking_writer)
{}

void EngineEventHelper::request_reset()
{
  m_board_state->reset();
}

void EngineEventHelper::request_myturn(const bool value)
{
  unique_ptr<EngineEvent> turn_event(new MyTurnFlipEvent(value));
  m_engine->enqueue(move(turn_event));
}

void EngineEventHelper::request_pondering(const bool value)
{
  unique_ptr<EngineEvent> pondering_event(new PonderingFlipEvent(value));
  m_engine->enqueue(move(pondering_event));
}

void EngineEventHelper::request_deferred_pondering()
{
  unique_ptr<EngineEvent> pondering_event(new DeferredPonderingEvent());
  m_engine->enqueue(move(pondering_event));
}

void EngineEventHelper::request_force(const bool value)
{
  unique_ptr<EngineEvent> force_event(new ForceFlipEvent(value));
  m_engine->enqueue(move(force_event));
}

void EngineEventHelper::request_quit()
{
  m_engine->request_quit();
}

void EngineEventHelper::request_set_time(const std::chrono::milliseconds& time)
{
  unique_ptr<SetTimeEvent> set_time(new SetTimeEvent(time));
  m_engine->enqueue(move(set_time));
}

void EngineEventHelper::move_now()
{
  m_engine->weak_stop();
}

void EngineEventHelper::ping(const int number)
{
  unique_ptr<EngineEvent> ping_event(new PingEvent(m_writer, number));
  m_engine->enqueue(move(ping_event));
}

void EngineEventHelper::post(const bool value)
{
  m_thinking_writer->post(value);
}

bool EngineEventHelper::request_move(const IncompleteMove incomplete_move)
{
  if (!m_board_state->valid_move(incomplete_move)) {
    return false;
  }
  const Move move = m_board_state->create_move(incomplete_move);
  enqueue_move(move);
  return true;
}

bool EngineEventHelper::set_fen(const string& fen)
{
  ChessBoard board;
  if (!FenParser::parse(fen, &board)) {
    return false;
  }
  unique_ptr<SetBoardEvent> set_board_event(new SetBoardEvent(board));
  m_engine->enqueue(move(set_board_event));
  return true;
}

void EngineEventHelper::enqueue_move(const Move& move)
{
  unique_ptr<EngineEvent> move_event(new MoveEvent(move));
  m_engine->enqueue(std::move(move_event));

} // namespace olaf
}

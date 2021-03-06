#include "protocols/engineeventhelper.h"

#include "protocols/event/engineevent.h"
#include "protocols/event/moveevent.h"
#include "protocols/event/ponderingflipevent.h"
#include "protocols/event/forceflipevent.h"
#include "protocols/event/deferredponderingevent.h"
#include "protocols/event/myturnflipevent.h"
#include "protocols/event/pingevent.h"
#include "protocols/event/undoevent.h"
#include "protocols/event/settimeevent.h"
#include "protocols/event/setanalyzeevent.h"
#include "protocols/event/setlevelevent.h"
#include "olaf/rules/move.h"
#include "olaf/parse/fenparser.h"
#include "protocols/event/setboardevent.h"
#include "protocols/event/setdepthevent.h"
#include "protocols/event/setnpsevent.h"
#include "protocols/event/setegtpathevent.h"

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
  unique_ptr<SetTimeEvent> set_time(new SetTimeEvent(time, true));
  m_engine->enqueue(move(set_time));
}

void EngineEventHelper::request_set_opponent_time(const std::chrono::milliseconds& time)
{
  unique_ptr<SetTimeEvent> set_time(new SetTimeEvent(time, false));
  m_engine->enqueue(move(set_time));
}

void EngineEventHelper::request_set_depth(const int depth)
{
  unique_ptr<SetDepthEvent> set_depth(new SetDepthEvent(depth));
  m_engine->enqueue(move(set_depth));
}


void EngineEventHelper::request_set_nps(const int nps)
{
  unique_ptr<SetNpsEvent> set_nps(new SetNpsEvent(nps));
  m_engine->enqueue(move(set_nps));
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

Status EngineEventHelper::request_set_fen(const string& fen)
{
  ChessBoard board;
  const Status& status = FenParser::parse(fen, &board);
  if (!status.ok()) {
    return status;
  }
  unique_ptr<SetBoardEvent> set_board_event(new SetBoardEvent(board));
  m_engine->enqueue(move(set_board_event));
  return Status::valid();
}

bool EngineEventHelper::request_undo(int moves)
{
  if (m_board_state->undoable_moves_size() < moves) {
    return false;
  }
  unique_ptr<UndoEvent> undo_event(new UndoEvent(moves));
  m_engine->enqueue(move(undo_event));
  return true;
}

void EngineEventHelper::request_analyze(const bool value)
{
  unique_ptr<SetAnalyzeEvent> analyze_event(new SetAnalyzeEvent(value));
  m_engine->enqueue(move(analyze_event));
}

void EngineEventHelper::enqueue_move(const Move& move)
{
  unique_ptr<EngineEvent> move_event(new MoveEvent(move));
  m_engine->enqueue(std::move(move_event));
}

void EngineEventHelper::request_set_level(const int moves_to_play,
                                          const chrono::milliseconds& total_time,
                                          const chrono::milliseconds& increment)
{
  unique_ptr<EngineEvent> set_level_event(new SetLevelEvent(moves_to_play, total_time, increment));
  m_engine->enqueue(std::move(set_level_event));
}

void EngineEventHelper::request_set_egt_path(const string &path)
{
  unique_ptr<EngineEvent> set_egt_path_event(new SetEgtPathEvent(path));
  m_engine->enqueue(std::move(set_egt_path_event));
}

} // namespace olaf

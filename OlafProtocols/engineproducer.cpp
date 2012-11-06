#include "engineproducer.h"
#include "engineevent.h"
#include "moveevent.h"
#include "ponderingflipevent.h"
#include "forceflipevent.h"
#include "deferredponderingevent.h"
#include "myturnflipevent.h"
#include "pingevent.h"
#include "settimeevent.h"
#include "OlafRules/move.h"

using namespace std;

EngineProducer::EngineProducer(const shared_ptr<ProtocolWriter> &writer,
                               const shared_ptr<BoardState> &board_state,
                               const shared_ptr<EngineConsumer> &consumer,
                               const shared_ptr<ThinkingWriter> &thinking_writer):
  m_writer (writer),
  m_board_state (board_state),
  m_consumer (consumer),
  m_thinking_writer (thinking_writer)
{}

void EngineProducer::request_reset()
{
  m_board_state->reset();
}

void EngineProducer::request_myturn(bool value)
{
  shared_ptr<EngineEvent> turn_event (new MyTurnFlipEvent(value));
  m_consumer->enqueue(turn_event);
}

void EngineProducer::request_pondering(bool value)
{
  shared_ptr<EngineEvent> pondering_event (new PonderingFlipEvent(value));
  m_consumer->enqueue(pondering_event);
}

void EngineProducer::request_deferred_pondering()
{
  shared_ptr<EngineEvent> pondering_event (new DeferredPonderingEvent());
  m_consumer->enqueue(pondering_event);
}

void EngineProducer::request_force(bool value)
{
  shared_ptr<EngineEvent> force_event (new ForceFlipEvent(value));
  m_consumer->enqueue(force_event);
}

void EngineProducer::request_quit()
{
  m_consumer->request_quit();
}

void EngineProducer::request_set_time(const std::chrono::milliseconds &time)
{
  shared_ptr<SetTimeEvent> set_time (new SetTimeEvent(time));
  m_consumer->enqueue(set_time);
}

void EngineProducer::move_now()
{
  m_consumer->weak_stop();
}

void EngineProducer::ping(int number)
{
  shared_ptr<EngineEvent> ping_event (new PingEvent(m_writer, number));
  m_consumer->enqueue(ping_event);
}

void EngineProducer::post(bool value)
{
  m_thinking_writer->post(value);
}

bool EngineProducer::request_move(const Position &source, const Position &destination)
{
  if (!m_board_state->valid_move(source, destination)) {
    return false;
  }
  Move move = m_board_state->create_move(source, destination);
  enqueue_move(move);
  return true;
}

bool EngineProducer::request_move(const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  if (!m_board_state->valid_move(source, destination, conversion)) {
    return false;
  }
  Move move = m_board_state->create_move(source, destination, conversion);
  enqueue_move(move);
  return true;
}

void EngineProducer::enqueue_move(const Move &move)
{
  shared_ptr<EngineEvent> move_event (new MoveEvent(move));
  m_consumer->enqueue(move_event);
  m_board_state->move(move);
}

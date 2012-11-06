#ifndef ENGINEPRODUCER_H
#define ENGINEPRODUCER_H

#include "protocolwriter.h"
#include "engineconsumer.h"
#include "boardstate.h"
#include "OlafSearching/thinkingwriter.h"
#include <memory>
#include <chrono>

class EngineProducer
{
public:
  EngineProducer(const std::shared_ptr<ProtocolWriter> &writer,
                 const std::shared_ptr<BoardState> &board_state,
                 const std::shared_ptr<EngineConsumer> &consumer,
                 const std::shared_ptr<ThinkingWriter> &thinking_writer);

  void request_reset();

  void request_myturn(bool value);

  void request_pondering(bool value);

  void request_deferred_pondering();

  void request_force(bool value);

  void request_quit();

  void request_set_time(const std::chrono::milliseconds &time);

  void move_now();

  void ping(int number);

  void post(bool value);

  bool request_move(const Position &source, const Position &destination);

  bool request_move(const Position &source, const Position &destination, Piece::piece_index_t conversion);

private:
  void enqueue_move(const Move &move);

  std::shared_ptr<ProtocolWriter> m_writer;

  std::shared_ptr<BoardState> m_board_state;

  std::shared_ptr<EngineConsumer> m_consumer;

  std::shared_ptr<ThinkingWriter> m_thinking_writer;

};

#endif // ENGINEPRODUCER_H

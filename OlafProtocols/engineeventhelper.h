#ifndef ENGINEEVENTHELPER_H
#define ENGINEEVENTHELPER_H

#include "protocolwriter.h"
#include "engine.h"
#include "boardstate.h"
#include "OlafSearching/thinkingwriter.h"
#include <memory>
#include <chrono>

/**
 * @brief The EngineEventHelper class is a helper class for the class that
 *        reads the input received from the chess interface program. It creates
 *        events and sends them to the engine.
 */
class EngineEventHelper
{
public:
  /**
   * @brief EngineEventHelper not take ownership of any of the passed pointers.
   */
  EngineEventHelper(ProtocolWriter* writer,
                    BoardState* board_state,
                    Engine* consumer,
                    ThinkingWriter* thinking_writer);

  void request_reset();

  void request_myturn(bool value);

  void request_pondering(bool value);

  void request_deferred_pondering();

  void request_force(bool value);

  void request_quit();

  void request_set_time(const std::chrono::milliseconds& time);

  void move_now();

  void ping(int number);

  bool request_move(const Position& source, const Position& destination);

  bool request_move(const Position& source, const Position& destination, Piece::piece_index_t conversion);

  void post(bool value);

private:
  void enqueue_move(const Move& move);

  ProtocolWriter* const m_writer;

  BoardState* const m_board_state;

  Engine* const m_engine;

  ThinkingWriter* const m_thinking_writer;
};

#endif // ENGINEEVENTHELPER_H

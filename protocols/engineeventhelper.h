#ifndef ENGINEEVENTHELPER_H
#define ENGINEEVENTHELPER_H

#include "protocols/protocolwriter.h"
#include "protocols/engine.h"
#include "protocols/boardstate.h"
#include "olaf/search/thinkingwriter.h"
#include <memory>
#include <chrono>

namespace olaf
{

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

  void request_set_opponent_time(const std::chrono::milliseconds& time);

  void request_set_depth(int depth);

  void request_set_nps(int nps);

  void move_now();

  void ping(int number);

  bool request_move(IncompleteMove incomplete_move);

  void post(bool value);

  bool request_set_fen(const std::string& fen);

  /**
   * @brief undo undoes a given number of moves. One per default.
   *        Returns false if it is not possible to undo this many moves.
   */
  bool request_undo(int moves = 1);

  void request_analyze(bool value);

private:
  void enqueue_move(const Move& move);

  ProtocolWriter* const m_writer;

  BoardState* const m_board_state;

  Engine* const m_engine;

  ThinkingWriter* const m_thinking_writer;
};

} // namespace olaf

#endif // ENGINEEVENTHELPER_H

#ifndef ENGINE_H
#define ENGINE_H

#include "protocols/protocolwriter.h"
#include "protocols/event/engineevent.h"
#include "protocols/enginestate.h"
#include "protocols/boardstate.h"
#include "olaf/search/searcher.h"
#include "olaf/search/forcedstopper.h"
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

namespace olaf
{

/**
 * @brief The Engine class runs the algorithms to find moves and reacts to events.
 */
class Engine
{
public:
  Engine(ProtocolWriter* writer,
         std::unique_ptr<TranspositionTable> transposition_table,
         std::unique_ptr<PawnTable> pawn_table,
         std::unique_ptr<EgbbProber> egbb_prober,
         BoardState* board_state,
         std::unique_ptr<Searcher> searcher);

  void run();

  void enqueue(std::unique_ptr<EngineEvent> event);

  void weak_stop();

  void request_quit();

private:
  void handle_events();

  void move(const Move& move);

  std::mutex m_mutex;

  std::condition_variable m_condition_variable;

  EngineState m_state;

  ProtocolWriter* const m_writer;

  std::unique_ptr<Searcher> m_searcher;

  std::queue<std::unique_ptr<EngineEvent>> m_event_queue;

  std::atomic<bool> m_quit;
};

} // namespace olaf

#endif // ENGINE_H

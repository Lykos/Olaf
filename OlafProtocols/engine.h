#ifndef ENGINE_H
#define ENGINE_H

#include "protocolwriter.h"
#include "engineevent.h"
#include "enginestate.h"
#include "boardstate.h"
#include "OlafSearching/searcher.h"
#include "OlafSearching/forcedstopper.h"
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
  /**
   * @brief Engine takes ownership of searcher, but not of the two others.
   */
  Engine(ProtocolWriter* writer,
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

  std::unique_ptr<ForcedStopper> m_forced_stopper;

  std::unique_ptr<ForcedStopper> m_weak_stopper;

  ProtocolWriter* const m_writer;

  std::unique_ptr<Searcher> m_searcher;

  std::queue<std::unique_ptr<EngineEvent>> m_event_queue;

  std::atomic<bool> m_quit;
};

} // namespace olaf

#endif // ENGINE_H

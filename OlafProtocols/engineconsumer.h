#ifndef ENGINECONSUMER_H
#define ENGINECONSUMER_H

#include "protocolwriter.h"
#include "engineevent.h"
#include "enginestate.h"
#include "boardstate.h"
#include "OlafSearching/timedsearcher.h"
#include "OlafSearching/forcedstopper.h"
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

class EngineConsumer
{
public:
  EngineConsumer(const std::shared_ptr<ProtocolWriter> &writer,
                 const std::shared_ptr<BoardState> &board_state,
                 const std::shared_ptr<TimedSearcher> &searcher);

  void run();

  void enqueue(const std::shared_ptr<EngineEvent> &event);

  void weak_stop();

  void request_quit();

private:
  ChessBoard handle_events();

  void move(const Move &move);

  std::mutex m_mutex;

  std::condition_variable m_condition_variable;

  EngineState m_state;

  std::shared_ptr<ForcedStopper> m_forced_stopper;

  std::shared_ptr<ForcedStopper> m_weak_stopper;

  std::shared_ptr<ProtocolWriter> m_writer;

  std::shared_ptr<BoardState> m_board_state;

  std::shared_ptr<TimedSearcher> m_searcher;

  std::queue< std::shared_ptr<EngineEvent> > m_event_queue;

  std::atomic<bool> m_quit;

};

#endif // ENGINECONSUMER_H

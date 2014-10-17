#include "engine.h"

#include <cassert>

#include "OlafSearching/stopper.h"
#include "OlafRules/chessboard.h"

using namespace std;

Engine::Engine(ProtocolWriter* const writer,
               BoardState* board_state,
               unique_ptr<Searcher> searcher):
  m_state(board_state),
  m_forced_stopper(new ForcedStopper),
  m_weak_stopper(new ForcedStopper),
  m_writer(writer),
  m_searcher(std::move(searcher)),
  m_quit(false)
{}

void Engine::run()
{
  while (!m_quit) {
    handle_events();
    if (m_quit) {
      return;
    }
    if (m_state.pondering() || m_state.my_turn()) {
      SearchContext context = m_state.create_search_context(m_forced_stopper.get(),
                                                            m_weak_stopper.get());
      SearchResult result = m_searcher->search(&context);
      if (!result.valid()) {
        continue;
      }
      move(result.main_variation.back());
    }

  }
}

void Engine::handle_events()
{
  unique_lock<mutex> lock(m_mutex);
  m_condition_variable.wait(lock, [this] { return !m_event_queue.empty() || m_quit; });
  if (m_quit) {
    return;
  }
  while (!m_event_queue.empty()) {
    m_event_queue.front()->execute(&m_state);
    m_event_queue.pop();
  }
  m_forced_stopper.reset(new ForcedStopper);
  m_weak_stopper.reset(new ForcedStopper);
}

void Engine::enqueue(unique_ptr<EngineEvent> event)
{
  unique_lock<mutex> lock (m_mutex);
  m_forced_stopper->request_stop();
  m_event_queue.push(std::move(event));
  m_condition_variable.notify_one();
}

void Engine::weak_stop()
{
  unique_lock<mutex> lock (m_mutex);
  m_weak_stopper->request_stop();
}

void Engine::request_quit()
{
  unique_lock<mutex> lock (m_mutex);
  m_forced_stopper->request_stop();
  m_condition_variable.notify_one();
  m_quit = true;
}

void Engine::move(const Move &move)
{
  m_writer->move(move);
  m_state.flip_turn();
  m_state.board_state().move(move);
}

#include "engine.h"

#include <cassert>

#include "olaf/search/stopper.h"
#include "olaf/rules/chessboard.h"
#include "protocols/result.h"

using namespace std;

namespace olaf
{

Engine::Engine(ProtocolWriter* const writer,
               unique_ptr<TranspositionTable> transposition_table,
               unique_ptr<EgbbProber> egbb_prober,
               BoardState* const board_state,
               unique_ptr<Searcher> searcher):
  m_state(std::move(transposition_table), std::move(egbb_prober), board_state),
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
    if (m_state.force()) {
      continue;
    }
    SearchContext context = m_state.create_search_context();
    if (context.board.draw()) {
      m_writer->result(Result::Draw, context.board.draw_reason());
      continue;
    }
    if (m_state.my_turn() && !m_state.analyze()) {
      SearchResult result = m_searcher->search(&context);
      if (result.valid) {
        move(result.main_variation.back());
      }
    }
    if (m_state.pondering() || m_state.analyze()) {
      m_searcher->search(&context);
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
  // This has to happen while we are still holding the lock.
  // Otherwise, enqueueing of a move can still get the old stoppers resulting in infinite pondering.
  // It also has to happen after handling the events, otherwise the stoppers may get stopped immediately.
  m_state.reset_stoppers();
}

void Engine::enqueue(unique_ptr<EngineEvent> event)
{
  unique_lock<mutex> lock (m_mutex);
  m_state.stop();
  m_event_queue.push(std::move(event));
  m_condition_variable.notify_one();
}

void Engine::weak_stop()
{
  unique_lock<mutex> lock (m_mutex);
  m_state.weak_stop();
}

void Engine::request_quit()
{
  unique_lock<mutex> lock (m_mutex);
  m_state.stop();
  m_condition_variable.notify_one();
  m_quit = true;
}

void Engine::move(const Move &move)
{
  m_writer->move(move);
  m_state.flip_turn();
  m_state.board_state().move(move);
}

} // namespace olaf

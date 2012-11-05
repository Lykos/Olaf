#include "engineconsumer.h"
#include "OlafSearching/stopper.h"
#include "OlafRules/chessboard.h"
#include <iostream>

using namespace std;

EngineConsumer::EngineConsumer(const std::shared_ptr<ProtocolWriter> &writer,
                               const std::shared_ptr<BoardState> &board_state,
                               const std::shared_ptr<TimedSearcher> &searcher):
  m_forced_stopper (new ForcedStopper()),
  m_weak_stopper (new ForcedStopper()),
  m_writer (writer),
  m_board_state (board_state),
  m_searcher (searcher),
  m_quit (false)
{}

void EngineConsumer::run()
{
  while (!m_quit) {
    ChessBoard board = handle_events();
    if (m_quit) {
      return;
    }
    if (m_state.pondering() || m_state.my_turn()) {
      shared_ptr<Stopper> forced_stopper (static_pointer_cast<Stopper>(m_forced_stopper));
      shared_ptr<Stopper> weak_stopper (static_pointer_cast<Stopper>(m_weak_stopper));
      if (m_state.my_turn() && !m_state.force()) {
        m_searcher->time(m_state.time());
        SearchResult result = m_searcher->search_timed(board, forced_stopper, weak_stopper);
        move(result.main_variation().back());
      } else {
        m_searcher->search_untimed(board, forced_stopper);
      }
    }

  }
}

ChessBoard EngineConsumer::handle_events()
{
  unique_lock<mutex> lock (m_mutex);
  m_condition_variable.wait(lock, [this] { return !m_event_queue.empty() || m_quit; });
  if (m_quit) {
    return ChessBoard();
  }
  while (!m_event_queue.empty()) {
    m_event_queue.front()->execute(m_state);
    m_event_queue.pop();
  }
  shared_ptr<ForcedStopper> forced_stopper (new ForcedStopper());
  m_forced_stopper = forced_stopper;
  shared_ptr<ForcedStopper> weak_stopper (new ForcedStopper());
  m_weak_stopper = weak_stopper;
  ChessBoard board = m_board_state->board();
  return board;
}

void EngineConsumer::enqueue(const std::shared_ptr<EngineEvent> &event)
{
  unique_lock<mutex> lock (m_mutex);
  m_forced_stopper->request_stop();
  m_event_queue.push(event);
  m_condition_variable.notify_one();
}

void EngineConsumer::weak_stop()
{
  unique_lock<mutex> lock (m_mutex);
  m_weak_stopper->request_stop();
}

void EngineConsumer::request_quit()
{
  unique_lock<mutex> lock (m_mutex);
  m_forced_stopper->request_stop();
  m_condition_variable.notify_one();
  m_quit = true;
}

void EngineConsumer::move(const Move &move)
{
  Move mov (move);
  m_writer->move(mov);
  m_state.flip_turn();
  m_board_state->move(mov);
}

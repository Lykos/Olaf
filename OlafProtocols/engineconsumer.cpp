#include "engineconsumer.h"
#include "OlafSearching/stopper.h"
#include "OlafRules/chessboard.h"

using namespace std;

EngineConsumer::EngineConsumer(const std::shared_ptr<ProtocolWriter> &writer,
                               const std::shared_ptr<BoardState> &board_state,
                               const std::shared_ptr<TimedSearcher> &searcher):
  m_writer (writer),
  m_board_state (board_state),
  m_searcher (searcher)
{}

void EngineConsumer::run()
{
  while (!m_quit) {
    handle_events();
    if (m_state.pondering() || m_state.my_turn()) {
      shared_ptr<Stopper> stopper (static_pointer_cast<Stopper>(m_stopper));
      ChessBoard board (m_board_state->board());
      if (m_state.my_turn() && !m_state.force()) {
        SearchResult result = m_searcher->search(board, stopper);
        move(result.main_variation().back());
      } else {
        m_searcher->search(board, stopper);
      }
    }

  }
}

void EngineConsumer::handle_events()
{
  unique_lock<mutex> lock (m_mutex);
  m_condition_variable.wait(lock, [this] { return !m_event_queue.empty(); });
  while (!m_event_queue.empty()) {
    m_event_queue.front()->execute(m_state);
    m_event_queue.pop();
  }
  shared_ptr<ForcedStopper> stopper (new ForcedStopper());
  m_stopper = stopper;
}

void EngineConsumer::enqueue(const std::shared_ptr<EngineEvent> &event)
{
  unique_lock<mutex> lock (m_mutex);
  m_stopper->request_stop();
  m_event_queue.push(event);
  m_condition_variable.notify_all();
}

void EngineConsumer::request_quit()
{
  unique_lock<mutex> lock (m_mutex);
  m_stopper->request_stop();
  m_quit = true;
}

void EngineConsumer::move(const Move &move)
{
  Move mov (move);
  m_writer->move(mov);
  m_board_state->move(mov);
}

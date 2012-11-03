#include "engine.h"

using namespace std;

Engine::Engine(const boost::shared_ptr<MoveGenerator>& move_generator, const boost::shared_ptr<Searcher>& searcher, ProtocolWriter *protocol):
  m_move_generator (move_generator),
  m_searcher (searcher),
  m_writer (protocol)
{}

void Engine::request_reset()
{
  m_reset = true;
  request_stop();
}

void Engine::request_stop()
{
  m_stop = true;
  m_searcher->request_stop();
}

void Engine::start()
{
  m_worker = thread([](Engine& engine) { engine.run(); }, *this);
}

void Engine::resume(bool my_turn)
{
  m_my_turn = my_turn;
  m_condition_variable.notify_all();
}

void Engine::stop()
{
  if (m_reset) {
    reset();
  }
}

void Engine::run()
{
  while (!m_quit) {
    m_move_mutex.lock();
    while (!m_move_queue.empty()) {
      Move next_move = m_move_queue.front();
      next_move.execute(m_board);
      m_my_turn = !m_my_turn;
      m_move_queue.pop();
    }
    Move best_move = m_searcher->search(m_board);
    m_move_mutex.unlock();
    if (m_my_turn) {
      m_writer->move(best_move);
    }
  }
  stop();
}

void Engine::suspend()
{
  m_condition_variable.wait();
}

void Engine::reset()
{
  m_board = create_initial_board();
}

bool Engine::move(const Position &source, const Position &destination)
{
  if (!m_move_generator->valid_move(m_board, source, destination)) {
    return false;
  }
  Move move = m_move_generator->move(m_board, source, destination);
  m_move_mutex.lock();
  m_move_queue.push(move);
  request_stop();
  m_move_mutex.unlock();
  return true;
}

bool Engine::move(const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  if (!m_move_generator->valid_move(m_board, source, destination, conversion)) {
    return false;
  }
  Move move = m_move_generator->move(m_board, source, destination, conversion);
  m_move_mutex.lock();
  m_move_queue.push(move);
  request_stop();
  m_move_mutex.unlock();
  return true;
}

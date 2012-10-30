#include "engine.h"

using namespace std;

Engine::Engine(Protocol *protocol):
  m_protocol (protocol)
{}

void Engine::request_reset()
{
  m_reset = true;
  request_stop();
}

void Engine::request_stop()
{
  m_stop = true;
}

static void run(Engine* engine)
{

}

void Engine::start()
{

}

void Engine::stop()
{
  if (m_reset) {
    reset();
  }
}

void Engine::reset()
{
  m_board = create_initial_board();
}

bool Engine::move(const Position &source, const Position &destination)
{
  if (!m_move_generator.valid_move(m_board, source, destination)) {
    return false;
  }
  Move move = m_move_generator.move(m_board, source, destination);
  m_move_mutex.lock();
  m_move_queue.push(move);
  m_move_mutex.unlock();
  return true;
}

bool Engine::move(const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  if (!m_move_generator.valid_move(m_board, source, destination, conversion)) {
    return false;
  }
  Move move = m_move_generator.move(m_board, source, destination, conversion);
  m_move_mutex.lock();
  m_move_queue.push(move);
  m_move_mutex.unlock();
  return true;
}

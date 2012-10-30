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

void Engine::move(const Position &source, const Position &destination)
{
  m_move_mutex
}

void Engine::move(const Position &source, const Position &destination, Piece::piece_index_t conversion)
{

}

#ifndef ENGINE_H
#define ENGINE_H

#include "position.h"
#include "piece.h"
#include "chessboard.h"
#include "movegenerator.h"
#include "protocolwriter.h"
#include <mutex>
#include <thread>
#include <queue>

class Engine
{
public:
  Engine(Protocol *protocol);

  void request_reset();

  void start();

  void request_stop();

  bool move(const Position &source, const Position &destination);

  bool move(const Position &source, const Position &destination, Piece::piece_index_t conversion);

private:
  void stop();

  void reset();

  void make_moves();

  ChessBoard m_board;

  MoveGenerator m_move_generator;

  std::mutex m_move_mutex;

  std::queue m_move_queue;

  std::thread m_worker;

  volatile bool m_stop;

  volatile bool m_reset;

  ProtocolWriter *m_writer;

};

#endif // ENGINE_H

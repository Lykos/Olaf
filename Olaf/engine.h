#ifndef ENGINE_H
#define ENGINE_H

#include "position.h"
#include "piece.h"
#include "chessboard.h"
#include "movegenerator.h"
#include "protocolwriter.h"
#include "searcher.h"
#include <mutex>
#include <thread>
#include <queue>
#include <boost/shared_ptr.hpp>

class Engine
{
public:
  Engine(boost::shared_ptr<Searcher> searcher, ProtocolWriter *writer);

  void request_reset();

  void start();

  void resume(bool);

  void request_stop();

  void ponder(bool);

  bool move(const Position &source, const Position &destination);

  bool move(const Position &source, const Position &destination, Piece::piece_index_t conversion);

private:
  void stop();

  void reset();

  void make_moves();

  ChessBoard m_board;

  MoveGenerator m_move_generator;

  boost::shared_ptr<Searcher> m_searcher;

  std::mutex m_move_mutex;

  std::mutex m_resume_mutex;

  std::queue<Move> m_move_queue;

  std::thread m_worker;

  volatile bool m_stop;

  volatile bool m_reset;

  volatile bool m_ponder;

  volatile bool m_my_turn;

  ProtocolWriter *m_writer;

};

#endif // ENGINE_H

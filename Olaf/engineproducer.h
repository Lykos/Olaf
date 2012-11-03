#ifndef ENGINEPRODUCER_H
#define ENGINEPRODUCER_H

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
#include <condition_variable>

class EngineProducer
{
public:
  EngineProducer(const boost::shared_ptr<MoveGenerator>& move_generator);

  void request_reset();

  void start();

  void resume(bool);

  void request_stop();

  void request_quit();

  void ponder(bool);

  void run();

  bool move(const Position &source, const Position &destination);

  bool move(const Position &source, const Position &destination, Piece::piece_index_t conversion);

private:
  void stop();

  void reset();

  void suspend();

  void make_moves();

  ChessBoard m_board;

  boost::shared_ptr<MoveGenerator> m_move_generator;

  boost::shared_ptr<Searcher> m_searcher;

  std::mutex m_move_mutex;

  std::mutex m_resume_mutex;

  std::queue<Move> m_move_queue;

  std::thread m_worker;

  std::condition_variable m_condition_variable;

  volatile bool m_stop;

  volatile bool m_reset;

  volatile bool m_ponder;

  volatile bool m_my_turn;

  volatile bool m_quit;

  ProtocolWriter *m_writer;

};

#endif // ENGINEPRODUCER_H

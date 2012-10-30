#ifndef ENGINE_H
#define ENGINE_H

#include "position.h"
#include "piece.h"
#include "chessboard.h"
#include <mutex>
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

  std::mutex m_move_mutex;

  std::queue moves;

  bool m_stop;

  bool m_reset;

  Protocol *m_protocol;

};

#endif // ENGINE_H

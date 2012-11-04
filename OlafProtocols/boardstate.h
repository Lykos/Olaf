#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "OlafSearching/movecreator.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/piece.h"
#include "OlafRules/position.h"
#include <memory>
#include <mutex>

class BoardState
{
public:
  BoardState(const std::shared_ptr<MoveCreator> &move_creator);

  ChessBoard board();

  void reset();

  void move(const Move &move);

  bool valid_move(const Position &source, const Position &destination);

  bool valid_move(const Position &source, const Position &destination, Piece::piece_index_t conversion);

  Move create_move(const Position &source, const Position &destination);

  Move create_move(const Position &source, const Position &destination, Piece::piece_index_t conversion);

private:
  std::shared_ptr<MoveCreator> m_move_creator;

  std::mutex m_mutex;

  ChessBoard m_board;

};

#endif // BOARDSTATE_H

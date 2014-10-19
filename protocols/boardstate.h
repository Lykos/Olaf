#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "olaf/rules/movecreator.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"
#include <memory>
#include <mutex>
#include <stack>

namespace olaf
{

/**
 * @brief The BoardState class is the engines interface to the chess board.
 */
class BoardState
{
public:
  ChessBoard copy_board() const;

  void set_board(const ChessBoard& board);

  void reset();

  void undo();

  void move(const Move& move);

  bool valid_move(const Position& source,
                  const Position& destination);

  bool valid_move(const Position& source,
                  const Position& destination,
                  Piece::piece_index_t conversion);

  Move create_move(const Position& source,
                   const Position& destination);

  Move create_move(const Position& source,
                   const Position& destination,
                   Piece::piece_index_t conversion);

private:
  mutable std::mutex m_mutex;

  ChessBoard m_board;

  std::stack<Move> m_moves;
};

} // namespace olaf

#endif // BOARDSTATE_H

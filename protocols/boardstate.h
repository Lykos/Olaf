#ifndef BOARDSTATE_H
#define BOARDSTATE_H

#include "olaf/rules/movechecker.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/position.h"
#include "olaf/rules/undoinfo.h"
#include "olaf/rules/move.h"
#include <memory>
#include <mutex>
#include <stack>
#include <utility>

namespace olaf
{

class Move;
class UndoInfo;

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

  bool valid_move(IncompleteMove incomplete_move) const;

  Move create_move(IncompleteMove incomplete_move) const;

  inline int undoable_moves_size() { return m_undoable_moves.size(); }

private:
  mutable std::mutex m_mutex;

  ChessBoard m_board;

  std::stack<std::pair<Move, UndoInfo>> m_undoable_moves;
};

} // namespace olaf

#endif // BOARDSTATE_H

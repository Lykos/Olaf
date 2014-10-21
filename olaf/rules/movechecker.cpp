#include "olaf/rules/movechecker.h"

#include <cassert>
#include <vector>

#include "olaf/rules/pawn.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/move.h"
#include "olaf/rules/undoinfo.h"

using namespace std;

namespace olaf
{

// static
bool MoveChecker::valid_move(const ChessBoard& board,
                             const IncompleteMove incomplete_move)
{
  if (!pseudo_valid_move(board, incomplete_move)) {
    return false;
  } else {
    UndoInfo undo_info;
    ChessBoard try_board(board);
    Move::complete(incomplete_move, try_board).execute(&try_board, &undo_info);
    return !is_killable(try_board);
  }
}

// static
bool MoveChecker::pseudo_valid_move(const ChessBoard& board,
                                    const IncompleteMove incomplete_move)
{
  const Position src(incomplete_move.source());
  return board.friendd(src)
      && board.turn_board().piece(src).can_move(incomplete_move, board);
}

// static
bool MoveChecker::is_killable(const ChessBoard& board)
{
  static const Piece::piece_index_t king_index =
      PieceSet::instance().king().piece_index();
  const BitBoard king_captures =
      board.noturn_board().piece_board(king_index).bit_board() | board.king_captures();
  if (king_captures == 0) {
    return false;
  }
  const vector<Position>& king_positions = king_captures.positions();
  if (king_positions.empty()) {
    return false;
  }
  for (const PieceBoard& piece_board : board.turn_board().piece_boards()) {
    const Piece& piece = piece_board.piece();
    for (Position source : piece_board.positions()) {
      for (const Position& king_position : king_positions) {
        static const Pawn& pawn = PieceSet::instance().pawn();
        static const Piece::piece_index_t queen_index =
            PieceSet::instance().queen().piece_index();
        if (piece.can_move(Move::incomplete(source, king_position), board)) {
          return true;
        } else if (&piece == &pawn
                   && pawn.can_move(Move::incomplete_promotion(source, king_position, queen_index), board)) {
          return true;
        }
      }
    }
  }
  return false;
}

} // namespace olaf

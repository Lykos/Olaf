#include "olaf/search/simplemovecreator.h"

#include <cassert>
#include <vector>

#include "olaf/rules/pawn.h"
#include "olaf/rules/pieceset.h"

using namespace std;

namespace olaf
{

bool SimpleMoveCreator::valid_move(const ChessBoard& board,
                                   const Position source,
                                   const Position destination)
{
  if (!pseudo_valid_move(board, source, destination)) {
    return false;
  } else {
    ChessBoard try_board(board);
    Move move = create_move(try_board, source, destination);
    move.execute(&try_board);
    return !is_killable(try_board);
  }
}

bool SimpleMoveCreator::valid_move(const ChessBoard& board,
                                   const Position source,
                                   const Position destination,
                                   Piece::piece_index_t conversion)
{
  if (!pseudo_valid_move(board, source, destination, conversion)) {
    return false;
  } else {
    ChessBoard try_board(board);
    Move move = create_move(try_board, source, destination, conversion);
    move.execute(&try_board);
    return !is_killable(try_board);
  }
}

bool SimpleMoveCreator::pseudo_valid_move(const ChessBoard& board,
                                          const Position source,
                                          const Position destination)
{
  return board.friendd(source)
      && board.turn_board().piece(source).can_move(source, destination, board);
}

bool SimpleMoveCreator::pseudo_valid_move(const ChessBoard& board,
                                          const Position source,
                                          const Position destination,
                                          Piece::piece_index_t conversion)
{
  const Pawn& pawn = PieceSet::instance().pawn();
  return board.friendd(source)
      && board.turn_board().piece(source) == pawn
      && pawn.can_move(source, destination, board, conversion);
}

Move SimpleMoveCreator::create_move(const ChessBoard& board,
                                    const Position source,
                                    const Position destination)
{
  assert(board.friendd(source));
  return board.turn_board().piece(source).move(source, destination, board);
}

Move SimpleMoveCreator::create_move(const ChessBoard& board,
                                    const Position source,
                                    const Position destination,
                                    const Piece::piece_index_t conversion)
{
  static const Pawn& pawn = PieceSet::instance().pawn();
  assert(board.friendd(source));
  assert(board.turn_board().piece(source) == pawn);
  return pawn.move(source, destination, board, conversion);
}

bool SimpleMoveCreator::is_killable(const ChessBoard& board)
{
  static const Piece::piece_index_t king_index =
      PieceSet::instance().king().piece_index();
  vector<Position> king_positions = board.noturn_board().piece_board(king_index).positions();
  assert(king_positions.size() <= 1);
  const vector<Position>& king_capture_positions = board.king_capture_positions();
  king_positions.insert(king_positions.end(),
                        king_capture_positions.begin(),
                        king_capture_positions.end());
  if (king_positions.empty()) {
    return false;
  }
  for (const PieceBoard& piece_board : board.turn_board().piece_boards()) {
    const Piece& piece = piece_board.piece();
    for (Position source : piece_board.positions()) {
      for (const Position king_position : king_positions) {
        static const Pawn& pawn = PieceSet::instance().pawn();
        static const Piece::piece_index_t queen_index =
            PieceSet::instance().queen().piece_index();
        if (piece.can_move(source, king_position, board)) {
          return true;
        } else if (&piece == &pawn
                   && pawn.can_move(source, king_position, board,
                                    queen_index)) {
          return true;
        }
      }
    }
  }
  return false;

} // namespace olaf
}

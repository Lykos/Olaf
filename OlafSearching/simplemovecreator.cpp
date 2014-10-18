#include "simplemovecreator.h"

#include <vector>

#include "OlafRules/pawn.h"
#include "OlafRules/pieceset.h"

using namespace std;

bool SimpleMoveCreator::valid_move(const ChessBoard& board,
                                   const Position& source,
                                   const Position& destination)
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
                                   const Position& source,
                                   const Position& destination,
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
                                          const Position& source,
                                          const Position& destination)
{
  return board.friendd(source)
      && board.turn_board().piece(source).can_move(source, destination, board);
}

bool SimpleMoveCreator::pseudo_valid_move(const ChessBoard& board,
                                          const Position& source,
                                          const Position& destination,
                                          Piece::piece_index_t conversion)
{
  const Pawn& pawn = PieceSet::instance().pawn();
  return board.friendd(source)
      && board.turn_board().piece(source) == pawn
      && pawn.can_move(source, destination, board, conversion);
}

Move SimpleMoveCreator::create_move(const ChessBoard& board,
                                    const Position& source,
                                    const Position& destination)
{
  return board.turn_board().piece(source).move(source, destination, board);
}

Move SimpleMoveCreator::create_move(const ChessBoard& board,
                                    const Position& source,
                                    const Position& destination,
                                    const Piece::piece_index_t conversion)
{
  const Pawn& pawn = PieceSet::instance().pawn();
  return pawn.move(source, destination, board, conversion);
}

bool SimpleMoveCreator::is_killable(const ChessBoard& board)
{
  vector<Position> king_positions = board.king_capture_positions();
  vector<Position> killers;
  for (const Position& position : board.positions()) {
    if (board.friendd(position)) {
      killers.emplace_back(position);
    } else if (board.opponent(position)
               && board.noturn_board().piece_index(position)
               == PieceSet::instance().king().piece_index()) {
      king_positions.emplace_back(position);
    }
  }
  if (king_positions.empty()) {
    return false;
  }
  for (const Position& killer : killers) {
    for (const Position& king_position : king_positions) {
      if (pseudo_valid_move(board, killer, king_position)) {
        return true;
      } else if (pseudo_valid_move(board, killer, king_position,
                                   PieceSet::instance().queen().piece_index())) {
        return true;
      }
    }
  }
  return false;
}

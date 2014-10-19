#include "olaf/search/simplemovegenerator.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/pieceboard.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/movecreator.h"

#include <memory>
#include <iostream>

using namespace std;

namespace olaf
{

vector<Move> SimpleMoveGenerator::generate_moves(const ChessBoard& board)
{
  vector<Move> moves;
  for (const PieceBoard& piece_board : board.turn_board().piece_boards()) {
    const Piece& piece = piece_board.piece();
    for (Position source : piece_board.positions()) {
      vector<Move> piece_moves = piece.moves(source, board);
      for (Move& move : piece_moves) {
        moves.emplace_back(std::move(move));
      }
    }
  }
  return moves;
}

bool SimpleMoveGenerator::valid_move(const ChessBoard& board,
                                     const Move& move)
{
  if (move.is_conversion()) {
    return MoveCreator::valid_move(board,
                                   move.source(),
                                   move.destination(),
                                   move.created_piece());
  } else {
    return MoveCreator::valid_move(board,
                                   move.source(),
                                   move.destination());
  }
}

vector<Move> SimpleMoveGenerator::generate_valid_moves(const ChessBoard& board)
{
  vector<Move> moves = generate_moves(board);
  vector<Move> result;
  for (const Move& move : moves) {
    if (valid_move(board, move)) {
      result.push_back(move);
    }
  }
  return result;

} // namespace olaf
}

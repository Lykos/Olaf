#include "olaf/search/simplemovegenerator.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/pieceboard.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"

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
      const vector<Move>& piece_moves = piece.moves(source, board);
      moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
    }
  }
  return moves;
}

vector<Move> SimpleMoveGenerator::generate_valid_moves(const ChessBoard& board)
{
  vector<Move> moves = generate_moves(board);
  vector<Move> result;
  for (const Move move : moves) {
    if (MoveChecker::valid_move(board, move)) {
      result.push_back(move);
    }
  }
  return result;

} // namespace olaf
}

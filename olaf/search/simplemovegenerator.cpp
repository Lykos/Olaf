#include "olaf/search/simplemovegenerator.h"
#include "olaf/rules/bitboard.h"
#include "olaf/rules/position.h"
#include "olaf/rules/piece.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/magicmoves.h"
#include "olaf/rules/magicnumbers.h"

#include <memory>
#include <iostream>

using namespace std;

namespace olaf
{

static inline void add_moves(const Position& source,
                             BitBoard destinations,
                             const ChessBoard& board,
                             vector<Move>* const moves)
{
  while (destinations) {
    moves->push_back(MoveChecker::complete(source, destinations.next_position(), board));
  }
}

static inline void add_pawn_moves(const Position& source,
                                  BitBoard destinations,
                                  const ChessBoard& board,
                                  vector<Move>* const moves)
{
  if (destinations & BitBoard(MagicNumbers::c_promotion_rows[static_cast<int>(board.turn_color())])) {
    while (destinations) {
      Position destination = destinations.next_position();
      moves->push_back(MoveChecker::complete_promotion(source, destination, PieceSet::c_rook_index, board));
      moves->push_back(MoveChecker::complete_promotion(source, destination, PieceSet::c_knight_index, board));
      moves->push_back(MoveChecker::complete_promotion(source, destination, PieceSet::c_bishop_index, board));
      moves->push_back(MoveChecker::complete_promotion(source, destination, PieceSet::c_queen_index, board));
    }
  } else {
    add_moves(source, destinations, board, moves);
  }
}

vector<Move> SimpleMoveGenerator::generate_moves(const ChessBoard& board)
{
  vector<Move> moves;
  const ColorBoard& turn_board = board.turn_board();
  for (BitBoard sources = turn_board.piece_board(PieceSet::c_rook_index); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_rook(source, board), board, &moves);
  }
  for (BitBoard sources = turn_board.piece_board(PieceSet::c_knight_index); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_knight(source, board), board, &moves);
  }
  for (BitBoard sources = turn_board.piece_board(PieceSet::c_bishop_index); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_bishop(source, board), board, &moves);
  }
  for (BitBoard sources = turn_board.piece_board(PieceSet::c_queen_index); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_queen(source, board), board, &moves);
  }
  for (BitBoard sources = turn_board.piece_board(PieceSet::c_king_index); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_king(source, board), board, &moves);
  }
  for (BitBoard sources = turn_board.piece_board(PieceSet::c_pawn_index); sources;) {
    const Position source = sources.next_position();
    add_pawn_moves(source, MagicMoves::moves_pawn(source, board), board, &moves);
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

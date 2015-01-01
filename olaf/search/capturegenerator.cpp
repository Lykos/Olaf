#include "olaf/search/capturegenerator.h"

#include <vector>

#include "olaf/rules/move.h"
#include "olaf/rules/pieceset.h"
#include "olaf/rules/chessboard.h"
#include "olaf/rules/movechecker.h"
#include "olaf/rules/magicnumbers.h"
#include "olaf/rules/magicmoves.h"

using namespace std;

namespace olaf
{

static inline void add_moves(const Position source,
                             BitBoard destinations,
                             const ChessBoard& board,
                             vector<Move>* const moves)
{
  destinations = destinations & board.opponents();
  while (destinations) {
    moves->push_back(MoveChecker::complete(source, destinations.next_position(), board));
  }
}

static inline void add_pawn_move(const Position source,
                                  BitBoard destinations,
                                  const ChessBoard& board,
                                  vector<Move>* const moves)
{
  if (destinations & BitBoard(MagicNumbers::c_promotion_rows[static_cast<int>(board.turn_color())])) {
    destinations = destinations & board.opponents();
    while (destinations) {
      moves->push_back(MoveChecker::complete_promotion(source, destinations.next_position(),
                                                       PieceSet::c_queen_index, board));
    }
  } else {
    add_moves(source, destinations, board, moves);
  }
}

CaptureGenerator::CaptureGenerator(unique_ptr<MoveGenerator> generator):
  m_generator(move(generator))
{}

vector<Move> CaptureGenerator::generate_moves(const ChessBoard& board)
{
  vector<Move> moves;
  for (BitBoard sources = board.rook_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_rook(source, board), board, &moves);
  }
  for (BitBoard sources = board.knight_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_knight(source, board), board, &moves);
  }
  for (BitBoard sources = board.bishop_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_bishop(source, board), board, &moves);
  }
  for (BitBoard sources = board.queen_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_queen(source, board), board, &moves);
  }
  for (BitBoard sources = board.king_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    add_moves(source, MagicMoves::moves_king(source, board), board, &moves);
  }
  for (BitBoard sources = board.pawn_board(board.turn_color()); sources;) {
    const Position source = sources.next_position();
    add_pawn_move(source, MagicMoves::moves_pawn(source, board), board, &moves);
  }
  return moves;
}

vector<Move> CaptureGenerator::generate_valid_moves(const ChessBoard& board)
{
  vector<Move> moves = generate_moves(board);
  vector<Move> result;
  for (const Move move : moves) {
    if (MoveChecker::valid_move(board, move)) {
      result.push_back(move);
    }
  }
  return result;
}

} // namespace olaf

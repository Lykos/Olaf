#include "movegenerator.h"
#include "bitboard.h"
#include "position.h"
#include "piece.h"

using namespace std;

vector<Move> MoveGenerator::generate_moves(const ChessBoard &board)
{
  vector<Move> moves;
  for (const PieceBoard &piece_board : board.turn_board().piece_boards()) {
    const Piece &piece = piece_board.piece();
    for (Position::row_t row = 0; row < Position::ROW_SIZE; ++row) {
      for (Position::row_t column = 0; column < Position::COLUMN_SIZE; ++column) {
        Position source (row, column);
        if (piece_board.get(source)) {
          vector<Move> piece_moves = piece.moves(source, board);
          moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
      }
    }
  }
  return moves;
}

bool MoveGenerator::valid_move(const ChessBoard &board, const Position &source, const Position &destination)
{
  return board.friendd(source) && board.turn_board().piece(source).can_move(source, destination, board);
}

bool MoveGenerator::valid_move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  const Pawn& pawn = *PieceSet::instance().pawn();
  return board.friendd(source) && board.turn_board().piece(source) == pawn && pawn.can_move(source, destination, board, conversion);
}

Move move(const ChessBoard &board, const Position &source, const Position &destination)
{
  return board.turn_board().piece(source).move(source, destination, board);
}

Move move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion)
{
  const Pawn& pawn = *PieceSet::instance().pawn();
  return pawn.move(source, destination, board, conversion);
}

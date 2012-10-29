#include "movegenerator.h"
#include "bitboard.h"
#include "position.h"
#include "piece.h"

using namespace std;

vector<Move> MoveGenerator::generate_moves(const ChessBoard &board)
{
  BitBoard opponents (0);
  BitBoard friends (0);
  for (const PieceBoard &piece_board : board.noturn_board().piece_boards()) {
    opponents = opponents | piece_board;
  }
  for (const PieceBoard &piece_board : board.turn_board().piece_boards()) {
    friends = friends | piece_board;
  }
  vector<Move> moves;
  for (const PieceBoard &piece_board : board.turn_board().piece_boards()) {
    const Piece &piece = piece_board.piece();
    for (Position::row_t row = 0; row < Position::ROW_SIZE; ++row) {
      for (Position::row_t column = 0; column < Position::COLUMN_SIZE; ++column) {
        Position source (row, column);
        if (piece_board.get(source)) {
          vector<Move> piece_moves = piece.moves(source, board, opponents, friends);
          moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
        }
      }
    }
  }
  return moves;
}

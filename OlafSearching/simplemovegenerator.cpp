#include "simplemovegenerator.h"
#include "OlafRules/bitboard.h"
#include "OlafRules/position.h"
#include "OlafRules/piece.h"
#include <memory>
#include <iostream>

using namespace std;

vector<Move> SimpleMoveGenerator::generate_moves(const ChessBoard& board)
{
  vector<Move> moves;
  for (const PieceBoard& piece_board : board.turn_board().piece_boards()) {
    const Piece& piece = piece_board.piece();
    for (Position::row_t row = 0; row < Position::c_row_size; ++row) {
      for (Position::row_t column = 0; column < Position::c_column_size; ++column) {
        Position source(row, column);
        if (piece_board.get(source)) {
          vector<Move> piece_moves = piece.moves(source, board);
          for (Move& move : piece_moves) {
            moves.push_back(std::move(move));
          }
        }
      }
    }
  }
  return moves;
}

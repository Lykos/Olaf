#include "simplemovegenerator.h"
#include "bitboard.h"
#include "position.h"
#include "piece.h"
#include "pieceboard.h"
#include "chessboard.h"

#include <memory>
#include <iostream>

using namespace std;

namespace olaf
{

SimpleMoveGenerator::SimpleMoveGenerator(unique_ptr<MoveCreator> creator):
  m_creator(move(creator))
{}

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

bool SimpleMoveGenerator::valid_move(const ChessBoard& board,
                                     const Move& move)
{
  if (move.is_conversion()) {
    return m_creator->valid_move(board,
                                 move.source(),
                                 move.destination(),
                                 move.created_piece());
  } else {
    return m_creator->valid_move(board,
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

#include "simplemovegenerator.h"
#include "OlafRules/bitboard.h"
#include "OlafRules/position.h"
#include "OlafRules/piece.h"
#include <memory>
#include <iostream>

using namespace std;

SimpleMoveGenerator::SimpleMoveGenerator(unique_ptr<MoveCreator> creator):
  m_creator(move(creator))
{}

vector<Move> SimpleMoveGenerator::generate_moves(const ChessBoard& board)
{
  vector<Move> moves;
  for (const PieceBoard& piece_board : board.turn_board().piece_boards()) {
    const Piece& piece = piece_board.piece();
    for (const Position& source : piece_board.positions()) {
      if (piece_board.get(source)) {
        vector<Move> piece_moves = piece.moves(source, board);
        for (Move& move : piece_moves) {
          moves.push_back(std::move(move));
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
}

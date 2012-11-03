#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "move.h"
#include "chessboard.h"
#include "piece.h"
#include <vector>

class MoveGenerator
{
public:
  virtual std::vector<Move> generate_moves(const ChessBoard& board) = 0;

  virtual bool valid_move(const ChessBoard &board, const Position &source, const Position &destination) = 0;

  virtual bool valid_move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion) = 0;

  virtual Move move(const ChessBoard &board, const Position &source, const Position &destination) = 0;

  virtual Move move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion) = 0;

};

#endif // MOVEGENERATOR_H

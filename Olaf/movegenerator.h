#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include "move.h"
#include "chessboard.h"
#include "piece.h"
#include <vector>

class MoveGenerator
{
public:
  std::vector<Move> generate_moves(const ChessBoard& board);

  bool valid_move(const ChessBoard &board, const Position &source, const Position &destination);

  bool valid_move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion);

  Move move(const ChessBoard &board, const Position &source, const Position &destination);

  Move move(const ChessBoard &board, const Position &source, const Position &destination, Piece::piece_index_t conversion);

};

#endif // MOVEGENERATOR_H

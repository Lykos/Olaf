#ifndef SIMPLEMOVECREATOR_H
#define SIMPLEMOVECREATOR_H

#include "movecreator.h"
#include "OlafRules/piece.h"
#include "OlafRules/move.h"
#include "OlafRules/chessboard.h"
#include "OlafRules/position.h"

class SimpleMoveCreator : public MoveCreator
{
public:
  bool valid_move(const ChessBoard& board,
                  const Position& source,
                  const Position& destination) override;

  bool valid_move(const ChessBoard& board,
                  const Position& source,
                  const Position& destination,
                  Piece::piece_index_t conversion) override;

  Move create_move(const ChessBoard& board,
                   const Position& source,
                   const Position& destination) override;

  Move create_move(const ChessBoard& board,
                   const Position& source,
                   const Position& destination,
                   Piece::piece_index_t conversion) override;

};

#endif // SIMPLEMOVECREATOR_H

#ifndef MOVECREATOR_H
#define MOVECREATOR_H

#include "OlafRules/chessboard.h"
#include "OlafRules/position.h"
#include "OlafRules/move.h"
#include "OlafRules/piece.h"

/**
 * @brief The MoveCreator class is responsible for checking moves from the user and
 * creating the move objects.
 */
class MoveCreator
{
public:
  virtual bool valid_move(const ChessBoard& board,
                          const Position& source,
                          const Position& destination) = 0;

  virtual bool valid_move(const ChessBoard& board,
                          const Position& source,
                          const Position& destination,
                          Piece::piece_index_t conversion) = 0;

  virtual bool pseudo_valid_move(const ChessBoard& board,
                                 const Position& source,
                                 const Position& destination) = 0;

  virtual bool pseudo_valid_move(const ChessBoard& board,
                                 const Position& source,
                                 const Position& destination,
                                 Piece::piece_index_t conversion) = 0;

  virtual Move create_move(const ChessBoard& board,
                           const Position& source,
                           const Position& destination) = 0;

  virtual Move create_move(const ChessBoard& board,
                           const Position& source,
                           const Position& destination,
                           Piece::piece_index_t conversion) = 0;

};

#endif // MOVECREATOR_H

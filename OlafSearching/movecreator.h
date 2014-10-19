#ifndef MOVECREATOR_H
#define MOVECREATOR_H

#include "chessboard.h"
#include "position.h"
#include "move.h"
#include "piece.h"

namespace olaf
{

/**
 * @brief The MoveCreator class is responsible for checking moves from the user and
 * creating the move objects.
 */
class MoveCreator
{
public:
  virtual ~MoveCreator();

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

} // namespace olaf

#endif // MOVECREATOR_H

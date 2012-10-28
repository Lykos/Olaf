#ifndef COLORBOARD_H
#define COLORBOARD_H

#include <vector>
#include "pieceboard.h"
#include "piecepositions.h"

/**
 * @brief The ColorBoard class represents all the board information about one color, i.e. castling rights and
 * piece positions.
 */
class ColorBoard
{
public:
  ColorBoard(const std::vector<PiecePositions>&, const std::vector<PieceBoard>&);

  const std::vector<PiecePositions>& piece_positions() const;

  const std::vector<PieceBoard>& piece_boards() const;

private:
  std::vector<PiecePositions> m_piece_positions;

  std::vector<PieceBoard> m_piece_boards;

};

#endif // COLORBOARD_H

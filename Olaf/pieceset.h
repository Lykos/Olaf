#ifndef PIECESET_H
#define PIECESET_H

#include "piece.h"
#include <vector>

class PieceSet
{
public:
  typedef Piece::piece_index_t piece_index_t;

  static const piece_index_t ROOK_INDEX = 0;

  static const piece_index_t KNIGHT_INDEX = 1;

  static const piece_index_t BISHOP_INDEX = 2;

  static const piece_index_t QUEEN_INDEX = 3;

  static const piece_index_t KING_INDEX = 4;

  static const piece_index_t PAWN_INDEX = 5;

  ~PieceSet();

  PieceSet(PieceSet&& that) = delete;

  PieceSet(const PieceSet& that) = delete;

  PieceSet& operator=(PieceSet&& that) = delete;

  PieceSet& operator=(const PieceSet& that) = delete;

  const Piece* rook() const;

  const Piece* knight() const;

  const Piece* bishop() const;

  const Piece* queen() const;

  const Piece* king() const;

  const Piece* pawn() const;

  const std::vector<Piece*>& pieces() const;

  static const PieceSet& instance();

private:
  PieceSet();

  Piece* m_rook;

  Piece* m_knight;

  Piece* m_bishop;

  Piece* m_queen;

  Piece* m_king;

  Piece* m_pawn;

  std::vector<Piece*> m_pieces;

};

#endif // PIECESET_H

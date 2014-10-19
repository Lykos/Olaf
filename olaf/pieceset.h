#ifndef PIECESET_H
#define PIECESET_H

#include "piece.h"
#include "pawn.h"
#include <vector>
#include <memory>

namespace olaf
{

class PieceSet
{
public:
  typedef Piece::piece_index_t piece_index_t;

  PieceSet(PieceSet&& that) = delete;

  PieceSet(const PieceSet& that) = delete;

  PieceSet& operator=(PieceSet&& that) = delete;

  PieceSet& operator=(const PieceSet& that) = delete;

  const Piece& rook() const;

  const Piece& knight() const;

  const Piece& bishop() const;

  const Piece& queen() const;

  const Piece& king() const;

  const Pawn& pawn() const;

  const std::vector<const Piece*>& pieces() const;

  static const PieceSet& instance();

private:
  PieceSet();

  std::unique_ptr<const Piece> m_rook;

  std::unique_ptr<const Piece> m_knight;

  std::unique_ptr<const Piece> m_bishop;

  std::unique_ptr<const Piece> m_queen;

  std::unique_ptr<const Piece> m_king;

  std::unique_ptr<const Pawn> m_pawn;

  std::vector<const Piece*> m_pieces;

};

} // namespace olaf

#endif // PIECESET_H
